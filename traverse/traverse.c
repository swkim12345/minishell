/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:25:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/13 15:54:58 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	recur_traverse(t_ast_node *head, t_minishell *minishell, int recur_mode)
{
	if (!head)
		return (TRUE);
	if (recur_mode & 1)
		minishell->exit_code = traverse(head->left_node, minishell, 1, 3);
	if (head->cmd_node)
		return (TRUE);
	if ((recur_mode & 2) && (((head->flag & AND_FLAG) && !minishell->exit_code)
			|| ((head->flag & OR_FLAG) && minishell->exit_code)))
		minishell->exit_code = traverse(head->right_node, minishell, 1, 3);
	return (minishell->exit_code);
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
		traverse(head, minishell, 1, 3);
		exit(minishell->exit_code);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &minishell->exit_code, 0);
		set_signal_handler();
	}
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
		if (head->next_ast_node)
			head = head->next_ast_node;
		if (info.current_pipe != 0)
			close(info.pipe_list[info.current_pipe - 1].pipe_fd[0]);
		close(info.pipe_list[info.current_pipe].pipe_fd[1]);
	}
	close(info.pipe_list[info.current_pipe - 1].pipe_fd[0]);
	minishell->exit_code = wait_processes(info.pid, info.first_pid);
	if (head->right_node)
		minishell->exit_code = recur_traverse(head, minishell, 2);
	free(info.pipe_list);
	return (minishell->exit_code);
}

void	traverse_main_shell(t_ast_node *head, t_minishell *minishell, int recur_mode)
{
	if (head->cmd_node)
	{
		if ((recur_mode & 1) && head->cmd_node->str && head->cmd_node->str[0])
		{
			minishell->exit_code
				= process_command(head->cmd_node, minishell);
		}
	}
	else if (!head->cmd_node)
		minishell->exit_code = recur_traverse(head, minishell, recur_mode);
}

void	print_ast_node(t_ast_node *head)
{
	ft_printf("flag: [%p]\n", head);
	ft_printf("flag: [%d]\n", head->flag);
	ft_printf("left: [%p]\n", head->left_node);
	ft_printf("right: [%p]\n", head->right_node);
	ft_printf("next_ast_node: [%p]\n", head->next_ast_node);
	ft_printf("cmd_node: [%p]\n", head->cmd_node);
	ft_printf("red: [%p]\n", head->red);
	ft_printf("--------------------\n");
}

int	traverse(t_ast_node *head, t_minishell *minishell,
		int check_pipe, int recur_mode)
{
	int	stop_flag;

	stop_flag = FALSE;
	if (check_pipe && head->next_ast_node)
	{
		minishell->exit_code = pipe_traverse(head, minishell);
		set_signal_handler();
		reset_stdin_out(minishell);
		return (minishell->exit_code);
	}
	if (head->flag & BRACKET_FLAG)
	{
		minishell->exit_code = subshell_traverse(head, minishell);
		reset_stdin_out(minishell);
		return (minishell->exit_code);
	}
	if (!(minishell->flag & NOT_CHECK_RED))
		stop_flag = process_redirection(head, minishell);
	minishell->flag &= ~NOT_CHECK_RED;
	if (stop_flag == FALSE)
		traverse_main_shell(head, minishell, recur_mode);
	reset_stdin_out(minishell);
	return (minishell->exit_code);
}
