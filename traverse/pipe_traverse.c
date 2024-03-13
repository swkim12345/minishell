/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_traverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:20:13 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/13 15:55:37 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	wait_processes(pid_t last_pid, pid_t first_pid)
{
	int	wstatus;

	signal(SIGINT, SIG_IGN);
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
	info->ret = traverse(head, minishell, 0, 1);
	exit(info->ret);
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
