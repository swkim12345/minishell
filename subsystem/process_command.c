/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:20:26 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/13 11:42:16 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	is_builtin_fn(t_cmd_node *cmd_node)
{
	char	*lowercase_str;
	char	*cmd_name;

	cmd_name = cmd_node->cmd_name;
	lowercase_str = to_lowercase_str(cmd_node->cmd_name);
	if (str_equal(lowercase_str, "cd") || str_equal(lowercase_str, "echo")
		|| str_equal(lowercase_str, "env") || str_equal(lowercase_str, "pwd")
		|| str_equal(cmd_name, "export") || str_equal(cmd_name, "unset")
		|| str_equal(cmd_name, "exit"))
	{
		free(lowercase_str);
		return (1);
	}
	free(lowercase_str);
	return (0);
}

void	print_cmd_node(t_cmd_node *cmd_node)
{
	ft_printf("cmd_name: [%p]\n", cmd_node);
	ft_printf("cmd_name: [%s]\n", cmd_node->cmd_name);
	ft_printf("cmd_str: [%s]\n", cmd_node->str[1]);
	ft_printf("----------------\n");
}

int	process_command(t_cmd_node *cmd_node, t_minishell *minishell)
{
	t_pipe_traverse	*info;

	(void)info;
	cmd_node->cmd_name = cmd_node->str[0];
	// print_cmd_node(cmd_node);
	ft_unsetenv(minishell->export, "_");
	ft_setenv(minishell->env, "_", cmd_node->cmd_name);
	if (is_builtin_fn(cmd_node))
		minishell->exit_code = process_builtin(cmd_node, minishell);
	else
	{
		minishell->exit_code = process_extern_cmd(cmd_node, minishell);
		set_signal_handler();
	}
	return (minishell->exit_code);
}
