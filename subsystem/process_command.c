/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:20:26 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/17 14:37:39 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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

int	process_extern_cmd(t_cmd_node *cmd_node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_node->cmd_name, cmd_node->str, cmd_node->envp);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

int	process_command(t_cmd_node *cmd_node, t_minishell *minishell)
{
	cmd_node->cmd_name = cmd_node->str[0];
	if (is_builtin_fn(cmd_node))
		process_builtin(cmd_node);
	else
		process_extern_cmd(cmd_node);
}