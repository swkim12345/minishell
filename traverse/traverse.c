/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:25:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/08 15:04:49 by minsepar         ###   ########.fr       */
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

int	traverse(t_ast_node *head, t_minishell *minishell, int check_pipe)
{
	if (check_pipe && head->next_ast_node)
	{
		minishell->exit_code = pipe_traverse(head, minishell);
		reset_stdin_out(minishell);
		return (minishell->exit_code);
	}
	if (!(minishell->flag & NOT_CHECK_RED))
		process_redirection(head, minishell);
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
				minishell->exit_code
					= process_command(head->cmd_node, minishell);
		}
		else if (!head->cmd_node)
			minishell->exit_code = recur_traverse(head, minishell);
	}
	reset_stdin_out(minishell);
	return (minishell->exit_code);
}
