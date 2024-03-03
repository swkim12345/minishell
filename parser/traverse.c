/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:25:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/03 12:58:00 by minsepar         ###   ########.fr       */
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
		ft_printf("cmd_node : %s\n", head->cmd_node->str[0]);
		return (TRUE);
	}
	ft_printf("*******flag [%d]\n", head->flag);
	ft_printf("*******ret [%d]\n", ret);
	if (((head->flag & AND_FLAG) && !ret) ||
	((head->flag & OR_FLAG) && ret))
	{
		ft_printf("right node enter\n");
		ret = traverse(head->right_node, minishell, 1);
	}
	return (ret);
}

int	subshell_traverse(t_ast_node *head, t_minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_printf("subshell\n");
		head->flag = 0;
		process_redirection(head, minishell);
		traverse(head, minishell, 1);
		exit(minishell->exit_code);
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

	last_pid = waitpid(last_pid, &wstatus, 0);
	(void) first_pid;
	//if heredoc wait for first to finish and delete heredoc file
	// if (cmd->here_doc_flag)
	// {
	// 	if (waitpid(first_pid, NULL, 0) == -1)
	// 		unlink(g_path);
	// }
	while (1)
	{
		if (wait(NULL) == -1 && errno == ECHILD)
			break ;
	}
	return (wstatus);
}

t_pipe_io	*init_pipe_list(int num_pipe)
{
	t_pipe_io	*pipe_list;

	pipe_list = ft_calloc(sizeof(t_pipe_io) * (num_pipe + 1), 1);
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
	ft_printf("num_pipe: %d\n", info.num_pipe);
	info.pipe_list = init_pipe_list(info.num_pipe);
	dup2(minishell->stdin_fd, 0);
	dup2(minishell->stdout_fd, 1);
	ft_printf("change stdin stdout\n");
	while (++info.current_pipe < info.num_pipe)
	{
		pipe(info.pipe_list[info.current_pipe].pipe_fd);
		ft_printf("current pipe: %d\n", info.current_pipe);
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
		if (info.current_pipe != 0)
			close(info.pipe_list[info.current_pipe - 1].pipe_fd[0]);
		close(info.pipe_list[info.current_pipe].pipe_fd[1]);
	}
	close(info.pipe_list[info.current_pipe - 1].pipe_fd[0]);
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
	int			fd;

	cur_node = minishell->tmp_list->head;
	ft_printf("ast_ndoe->index: %d\n", index);
	while (--index > 0)
		cur_node = cur_node->next;
	ft_printf("heredoc_name: %s\n", cur_node->tmp);
	fd = open(cur_node->tmp, O_RDONLY);
	return (fd);
}

int	set_read_fd(t_redirection *redirect_node, t_minishell *minishell
		, t_ast_node *ast_node)
{
	int				fd;

	ft_printf("read_fd\n");
	if (redirect_node->flag & LT_SIGN)
	{
		fd = open(redirect_node->str, O_RDONLY);
		ft_printf("file: %s\n", redirect_node->str);
	}
	else if (redirect_node->flag & DB_LT_SIGN)
		fd = get_heredoc_fd(minishell, ast_node->index);
	else
		return (1);
	ft_printf("read fd: %d\n", fd);
	if (fd < 0)
	{
		minishell->error = set_error_msg(minishell->execute_name, redirect_node->str, 0, 0);
		print_error_msg(minishell->error, 0, 0);
		return (1);
	}
	if (dup2(fd, 0) == -1)
	{
		minishell->error = set_error_msg(minishell->execute_name, redirect_node->str, 0, 0);
		print_error_msg(minishell->error, 0, 0);
		return (1);
	}
	close(fd);
	return (0);
}

int set_write_fd(t_redirection *redirect_node, t_minishell *minishell)
{
	int				fd;

	ft_printf("write_fd\n");
	if (redirect_node->flag & GT_SIGN)
		fd = open(redirect_node->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (redirect_node->flag & DB_GT_SIGN)
		fd = open(redirect_node->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		return (1);
	ft_printf("write fd: %d\n", fd);
	ft_printf("write file: %s\n", redirect_node->str);
	if (fd < 0)
	{
		minishell->error = set_error_msg(minishell->execute_name, redirect_node->str, 0, 0);
		print_error_msg(minishell->error, 0, 0);
		return (1);
	}
	if (dup2(fd, 1) == -1)
	{
		minishell->error = set_error_msg(minishell->execute_name, redirect_node->str, 0, 0);
		print_error_msg(minishell->error, 0, 0);
		return (1);
	}
	close(fd);
	return (0);
}

int	process_redirection(t_ast_node *ast_node, t_minishell *minishell)
{
	t_redirection	*cur_node;
	int				error_check;
	int				i;

	ft_printf("redirection entered\n");
	cur_node = ast_node->red;
	error_check = 0;
	i = 0;
	while (cur_node)
	{
		ft_printf("cur_node: %s\n", cur_node->str);
		if ((cur_node->flag & LT_SIGN) || (cur_node->flag & DB_LT_SIGN))
			error_check = set_read_fd(cur_node, minishell, ast_node);
		else if ((cur_node->flag & GT_SIGN) || (cur_node->flag & DB_GT_SIGN))
			error_check = set_write_fd(cur_node, minishell);
		else
			ft_printf("not entered [%d]\n", cur_node->flag);
		if (error_check != 0)
			return (error_check);
		ft_printf("redirection success\n");
		cur_node = cur_node->next;
	}
	return (error_check);
}

int	traverse(t_ast_node *head, t_minishell *minishell, int check_pipe)
{
	ft_printf("traverse\n");
	print_ast_node(head);
	if (process_redirection(head, minishell) == 1)
		return (1); 
	if (!head && head->cmd_node->str[0] == NULL)
		minishell->exit_code = 0;
	else if (check_pipe && head->next_ast_node)
	{
		ft_printf("find next pipe\n");
		minishell->exit_code = pipe_traverse(head, minishell);
	}
	else if (head->flag & BRACKET_FLAG)
	{
		ft_printf("subshell traverse\n");
		minishell->exit_code = subshell_traverse(head, minishell);
	}
	else if (head->cmd_node)
	{
		ft_printf("process command\n");
		if (head->cmd_node->str[0])
			minishell->exit_code = process_command(head->cmd_node, minishell);
		else
			return (0);
	}
	else if (!head->cmd_node)
	{
		ft_printf("recur traverse\n");
		minishell->exit_code = recur_traverse(head, minishell);
	}
	dup2(minishell->stdin_fd, 0);
	dup2(minishell->stdout_fd, 1);
	ft_printf("change stdin stdout\n");
	return (minishell->exit_code);
}
