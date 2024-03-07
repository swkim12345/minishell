/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:25:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/07 17:58:33 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	recur_traverse(t_ast_node *head, t_minishell *minishell)
{
	int	ret;

	if (!head)
		return (TRUE);
	ret = traverse(head->left_node, minishell, 1);
	if (head->cmd_node)
		return (TRUE);
	if (((head->flag & AND_FLAG) && !ret)
		|| ((head->flag & OR_FLAG) && ret))
		ret = traverse(head->right_node, minishell, 1);
	return (ret);
}

int	subshell_traverse(t_ast_node *head, t_minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		head->flag &= ~BRACKET_FLAG;
		minishell->stdin_fd = dup(0);
		minishell->stdout_fd = dup(1);
		minishell->flag |= NOT_CHECK_RED;
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

	waitpid(last_pid, &wstatus, 0);
	(void) first_pid;
	while (1)
	{
		if (wait(NULL) == -1 && errno == ECHILD)
			break ;
	}
	return (WEXITSTATUS(wstatus));
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
		close(fd);
	}
	if (info->current_pipe != info->num_pipe - 1)
	{
		fd = info->pipe_list[info->current_pipe].pipe_fd[1];
		if (dup2(fd, 1) == -1)
			shell_error(minishell, 0, 0);
		close(fd);
	}
	close(info->pipe_list[info->current_pipe].pipe_fd[0]);
	close(info->pipe_list[info->current_pipe].pipe_fd[1]);
}

void	process_pipe_child(t_minishell *minishell, t_pipe_traverse *info,
			t_ast_node *head)
{
	minishell->flag |= PIPE_TRAVERSE;
	set_pipe_redirection(info, minishell);
	minishell->pipe_info = info;
	info->ret = traverse(head, minishell, 0);
	exit(info->ret);
}

int	pipe_traverse(t_ast_node *head, t_minishell *minishell)
{
	t_pipe_traverse	info;

	info.current_pipe = -1;
	info.num_pipe = get_num_pipe(head);
	info.pipe_list = init_pipe_list(info.num_pipe);
	dup2(minishell->stdin_fd, 0);
	dup2(minishell->stdout_fd, 1);
	while (++info.current_pipe < info.num_pipe)
	{
		pipe(info.pipe_list[info.current_pipe].pipe_fd);
		info.pid = fork();
		if (info.pid == 0)
			process_pipe_child(minishell, &info, head);
		if (info.current_pipe == 0)
			info.first_pid = info.pid;
		head = head->next_ast_node;
		if (info.current_pipe != 0)
			close(info.pipe_list[info.current_pipe - 1].pipe_fd[0]);
		close(info.pipe_list[info.current_pipe].pipe_fd[1]);
	}
	close(info.pipe_list[info.current_pipe - 1].pipe_fd[0]);
	minishell->exit_code = wait_processes(info.pid, info.first_pid);
	free(info.pipe_list);
	return (minishell->exit_code);
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
	if (cur_node == NULL)
		return (-1);
	while (--index > 0)
		cur_node = cur_node->next;
	fd = open(cur_node->tmp, O_RDONLY);
	return (fd);
}

int	get_file_num(char **file_list)
{
	int	i;

	i = 0;
	while (file_list[i])
		i++;
	return (i);
}

int	set_read_fd(t_redirection *redirect_node, t_minishell *minishell
		, t_ast_node *ast_node)
{
	int				fd;
	char			**file_list;

	if (redirect_node->flag & LT_SIGN)
	{
		file_list = string_parser(redirect_node->str, minishell);
		if (get_file_num(file_list) > 1 || file_list[0] == NULL)
		{
			minishell->error = set_error_msg(minishell->execute_name,
					redirect_node->str, 0, "ambiguous redirect");
			print_error_msg(minishell->error, 1, 0);
			free_2d_str(file_list);
			return (1);
		}
		fd = open(file_list[0], O_RDONLY);
		free_2d_str(file_list);
	}
	else if (redirect_node->flag & DB_LT_SIGN)
		fd = get_heredoc_fd(minishell, ast_node->index);
	else
		return (1);
	if (fd < 0)
	{
		minishell->error
			= set_error_msg(minishell->execute_name, redirect_node->str, 0, 0);
		print_error_msg(minishell->error, 0, 0);
		return (1);
	}
	if (dup2(fd, 0) == -1)
	{
		minishell->error
			= set_error_msg(minishell->execute_name, redirect_node->str, 0, 0);
		print_error_msg(minishell->error, 0, 0);
		return (1);
	}
	close(fd);
	return (0);
}

int set_write_fd(t_redirection *redirect_node, t_minishell *minishell)
{
	int				fd;
	char			**file_list;

	file_list = string_parser(redirect_node->str, minishell);
	if (get_file_num(file_list) > 1 || file_list[0] == NULL)
	{
		minishell->error = set_error_msg(minishell->execute_name,
				redirect_node->str, 0, "ambiguous redirect");
		print_error_msg(minishell->error, 1, 0);
		free_2d_str(file_list);
		return (1);
	}
	if (redirect_node->flag & GT_SIGN)
		fd = open(file_list[0], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (redirect_node->flag & DB_GT_SIGN)
		fd = open(file_list[0], O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
	{
		free_2d_str(file_list);
		return (1);
	}
	free_2d_str(file_list);
	if (fd < 0)
	{
		minishell->error
			= set_error_msg(minishell->execute_name, redirect_node->str, 0, 0);
		print_error_msg(minishell->error, 0, 0);
		return (1);
	}
	if (dup2(fd, 1) == -1)
	{
		minishell->error
			= set_error_msg(minishell->execute_name, redirect_node->str, 0, 0);
		print_error_msg(minishell->error, 0, 0);
		return (1);
	}
	close(fd);
	return (0);
}

int	process_redirection(t_ast_node *ast_node, t_minishell *minishell)
{
	t_redirection	*cur_node;

	cur_node = ast_node->red;
	minishell->exit_code = 0;
	while (cur_node)
	{
		if ((cur_node->flag & LT_SIGN) || (cur_node->flag & DB_LT_SIGN))
			minishell->exit_code = set_read_fd(cur_node, minishell, ast_node);
		else if ((cur_node->flag & GT_SIGN) || (cur_node->flag & DB_GT_SIGN))
			minishell->exit_code = set_write_fd(cur_node, minishell);
		if (minishell->exit_code != 0)
			return (minishell->exit_code);
		cur_node = cur_node->next;
	}
	return (minishell->exit_code);
}

int	traverse(t_ast_node *head, t_minishell *minishell, int check_pipe)
{
	if (check_pipe && head->next_ast_node)
	{
		minishell->exit_code = pipe_traverse(head, minishell);
		dup2(minishell->stdin_fd, 0);
		dup2(minishell->stdout_fd, 1);
		return (minishell->exit_code);
	}
	if (!(minishell->flag & NOT_CHECK_RED))
	{
		if (process_redirection(head, minishell) != 0)
			return (minishell->exit_code);
	}
	minishell->flag &= ~NOT_CHECK_RED;
	if (minishell->exit_code == 0)
	{
		if (!head && head->cmd_node->str[0] == NULL)
			minishell->exit_code = 0;
		else if (head->flag & BRACKET_FLAG)
			minishell->exit_code = subshell_traverse(head, minishell);
		else if (head->cmd_node)
		{
			if (head->cmd_node->str && head->cmd_node->str[0])
				minishell->exit_code = process_command(head->cmd_node, minishell);
			set_signal_handler();
		}
		else if (!head->cmd_node)
			minishell->exit_code = recur_traverse(head, minishell);
	}
	dup2(minishell->stdin_fd, 0);
	dup2(minishell->stdout_fd, 1);
	return (minishell->exit_code);
}
