/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:20:26 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/21 13:51:00 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subsystem.h"

/*
	cmd struct list
*/

int	is_builtin_fn(t_cmd_node *cmd_node)
{
	char	*str;

	str = cmd_node->cmd_name;
	if (str_equal(str, "echo") || str_equal(str, "pwd")
		|| str_equal(str, "pwd") || str_equal(str, "export")
		|| str_equal(str, "unset") || str_equal(str, "env")
		|| str_equal(str, "exit"))
		return (1);
	return (0);
}


int	process_extern_cmd(t_cmd_node *cmd_node, t_minishell *minishell)
{
	pid_t	pid;
	int		status;
	char	*execute_path;

	pid = fork();
	if (pid == 0)
	{
		execute_path = set_command_path(cmd_node, minishell);
		execve(cmd_node->cmd_name, cmd_node->str, minishell->envp);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

// int	set_read_fd(t_redirection *node, t_minishell *minishell)
// {
// 	int	fd;

// 	if (node->flag & LT_SIGN)
// 		fd = open(minishell->tmp_file, O_CREAT | O_TRUNC, 0777);
// 	else if (node->flag & DB_LT_SIGN)
		
// }

// int	process_redirection(t_cmd_node *cmd_node, t_minishell *minishell)
// {
// 	t_redirection	*cur_node;

// 	cur_node = cmd_node->red;
// 	while (cur_node)
// 	{
// 		if (cur_node->flag & LT_SIGN)
// 			set_read_fd(cur_node, minishell);
// 	}
// 	return (0);
// }

int	process_command(t_cmd_node *cmd_node, t_minishell *minishell)
{
	cmd_node->cmd_name = cmd_node->str[0];
	expand_argument(cmd_node);
	if (is_builtin_fn(cmd_node))
		process_builtin(cmd_node);
	else
		process_extern_cmd(cmd_node, minishell);
}
