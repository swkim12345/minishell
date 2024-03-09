/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:27:41 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/09 12:16:58 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	process_builtin(t_cmd_node *cmd_node, t_minishell *minishell)
{
	char	*cmd_name;

	cmd_name = to_lowercase_str(cmd_node->cmd_name);
	if (str_equal(cmd_name, "echo"))
		minishell->exit_code = ft_echo(cmd_node);
	else if (str_equal(cmd_name, "cd"))
		minishell->exit_code = ft_cd(cmd_node, minishell);
	else if (str_equal(cmd_name, "pwd"))
		minishell->exit_code = ft_pwd(minishell);
	else if (str_equal(cmd_name, "export"))
		minishell->exit_code = ft_export(cmd_node, minishell);
	else if (str_equal(cmd_name, "unset"))
		minishell->exit_code = ft_unset(cmd_node, minishell);
	else if (str_equal(cmd_name, "env"))
		minishell->exit_code = ft_env(minishell);
	else if (str_equal(cmd_name, "exit"))
		minishell->exit_code = ft_exit(cmd_node, minishell);
	free(cmd_name);
	return (minishell->exit_code);
}
