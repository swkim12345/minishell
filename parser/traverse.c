/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:25:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/28 17:12:11 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	recur_traverse(t_ast_node *head, t_minishell *minishell) //fork로 실행, wait를 통해 wait, 이후 pipe관련 처리
{
	int	ret;

	if (!head)
		return (TRUE); //fix 필요(true만 리턴하면 안됨.)
	if (head->red)
		process_redirection(head, minishell);
	ret = traverse(head->left_node, minishell, 1);
	if (head->cmd_node)
	{
		printf("cmd_node : %s\n", head->cmd_node->str[0]);
		return (TRUE);
	}
	if (head->log_opr)
		printf("str : %s\n", head->log_opr);
	if ((str_equal(head->log_opr, AND) && ret) ||
	(str_equal(head->log_opr, OR) && !ret))
		ret = traverse(head->right_node, minishell, 1);
	return (ret);
}

int	subshell_traverse(t_ast_node *head, t_minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		printf("subshell\n");
		head->flag = 0;
		process_redirection(head, minishell);
		traverse(head, minishell, 1);
	}
	else
		waitpid(pid, &minishell->exit_code, 0);
	return (WEXITSTATUS(minishell->exit_code));
}

int	get_num_pipe(t_ast_node *head)
{
	t_ast_node	*cur;
	int			num_pipe;

	num_pipe = 0;
	cur = head;
	while (cur)
	{
		cur = cur->next_ast_node;
		num_pipe++;
	}
	return (num_pipe);
}

int	wait_processes(pid_t last_pid, pid_t first_pid)
{
	int	wstatus;
	int	status_code;

	last_pid = waitpid(last_pid, &wstatus, 0);
	(void) first_pid;
	//if heredoc wait for first to finish and delete heredoc file
	// if (cmd->here_doc_flag)
	// {
	// 	if (waitpid(first_pid, NULL, 0) == -1)
	// 		unlink(g_path);
	// }
	if (WIFEXITED(wstatus))
		status_code = WEXITSTATUS(wstatus);
	while (1)
	{
		if (wait(NULL) == -1 && errno == ECHILD)
			break ;
	}
	return (status_code);
}

t_pipe_io	*init_pipe_list(int num_pipe)
{
	t_pipe_io	*pipe_list;

	pipe_list = malloc(sizeof(t_pipe_io) * (num_pipe + 1));
	ft_memset((void *)pipe_list, 0, sizeof(t_pipe_io) * (num_pipe + 1));
	return (pipe_list);
}

void	set_pipe_redirection(t_pipe_traverse *info, t_minishell *minishell)
{
	int	fd;

	if (info->current_pipe != 0)
	{
		fd = info->pipe_list[info->current_pipe - 1].pipe_fd[0];
		if (dup2(fd, 0) == -1)
			shell_error(minishell, 0, 0);
	}
	if (info->current_pipe != info->num_pipe - 1)
	{
		fd = info->pipe_list[info->current_pipe].pipe_fd[1];
		if (dup2(fd, 1) == -1)
			shell_error(minishell, 0, 0);
	}
}

int	pipe_traverse(t_ast_node *head, t_minishell *minishell)
{
	t_pipe_traverse	info;

	info.current_pipe = -1;
	info.num_pipe = get_num_pipe(head);
	printf("num_pipe: %d\n", info.num_pipe);
	info.pipe_list = init_pipe_list(info.num_pipe);
	while (++info.current_pipe < info.num_pipe)
	{
		pipe(info.pipe_list[info.current_pipe].pipe_fd);
		printf("current pipe: %d\n", info.current_pipe);
		info.pid = fork();
		if (info.pid == 0)
		{
			set_pipe_redirection(&info, minishell);
			info.ret = traverse(head, minishell, 0);
			exit(info.ret);
		}
		if (info.current_pipe == 0)
			info.first_pid = info.pid;
		head = head->next_ast_node;
	}
	info.ret = wait_processes(info.pid, info.first_pid);
	//free pipelist
	return (info.ret);
}

t_tmp_file	*get_heredoc_file(t_minishell *minishell, int index)
{
	t_tmp_file	*cur_node;

	cur_node = minishell->tmp_list->head;
	while (index > 0)
	{
		cur_node = cur_node->next;
		index--;
	}
	return (cur_node);
}

int	get_heredoc_fd(t_minishell *minishell, int index)
{
	t_tmp_file	*cur_node;

	cur_node = minishell->tmp_list->head;
	while (index > 0)
	{
		cur_node = cur_node->next;
		index--;
	}
	return (cur_node->fd);
}

int	set_read_fd(t_ast_node *ast_node, t_minishell *minishell)
{
	int				fd;
	t_redirection	*redirect_node;

	redirect_node = ast_node->red;
	if (redirect_node->flag & LT_SIGN)
		fd = open(redirect_node->str, O_RDONLY);
	else if (redirect_node->flag & DB_LT_SIGN)
		fd = get_heredoc_fd(minishell, ast_node->index);
	if (fd < 0)
	{
		print_error_msg(minishell->error, errno, 0);
		return (-1);
	}
	if (dup2(fd, 0) == -1)
		print_error_msg(minishell->error, errno, 0);
	close(fd);
	return (1);
}

int set_write_fd(t_ast_node *ast_node, t_minishell *minishell)
{
	int				fd;
	t_redirection	*redirect_node;

	redirect_node = ast_node->red;
	if (redirect_node->flag & GT_SIGN)
		fd = open(redirect_node->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (redirect_node->flag & DB_GT_SIGN)
		fd = open(redirect_node->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		print_error_msg(minishell->error, errno, 0);
		return (-1);
	}
	if (dup2(fd, 0) == -1)
		print_error_msg(minishell->error, errno, 0);
	close(fd);
}

int	process_redirection(t_ast_node *ast_node, t_minishell *minishell)
{
	t_redirection	*cur_node;
	int				error_check;
	int				i;

	cur_node = ast_node->red;
	error_check = 0;
	i = 0;
	while (cur_node)
	{
		if (cur_node->flag & LT_SIGN || cur_node->flag & DB_LT_SIGN)
			error_check = set_read_fd(ast_node, minishell);
		else if (cur_node->flag & GT_SIGN || cur_node->flag & DB_GT_SIGN)
			error_check = set_write_fd(ast_node, minishell);
		if (error_check != 0)
			return (error_check);
		cur_node = cur_node->next;
	}
	return (error_check);
}

int	traverse(t_ast_node *head, t_minishell *minishell, int check_pipe)
{
	int	ret;

	if (!head && head->cmd_node->str[0] == NULL)
		return (FUNC_FAIL);
	else if (check_pipe && head->next_ast_node)
	{
		printf("find next pipe\n");
		ret = pipe_traverse(head, minishell);
	}
	else if (head->flag & BRACKET_FLAG)
		ret = subshell_traverse(head, minishell);
	else if (head->cmd_node)
		process_command(head->cmd_node, minishell);
	else
		ret = recur_traverse(head, minishell);
	return (ret);
}
