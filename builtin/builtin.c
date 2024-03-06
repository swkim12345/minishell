/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:27:41 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/06 13:13:04 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	process_builtin(t_cmd_node *cmd_node, t_minishell *minishell)
{
	char	*cmd_name;
	int		ret;

	cmd_name = to_lowercase_str(cmd_node->cmd_name);
	ret = FUNC_SUC;
	if (str_equal(cmd_name, "echo"))
		ret = ft_echo(cmd_node);
	else if (str_equal(cmd_name, "cd"))
		ret = ft_cd(cmd_node, minishell);
	else if (str_equal(cmd_name, "pwd"))
		ret = ft_pwd(minishell);
	else if (str_equal(cmd_name, "export"))
		ret = ft_export(cmd_node, minishell);
	else if (str_equal(cmd_name, "unset"))
		ret = ft_unset(cmd_node, minishell);
	else if (str_equal(cmd_name, "env"))
		ret = ft_env(minishell);
	else if (str_equal(cmd_name, "exit"))
		ret = ft_exit(cmd_node, minishell);
	free(cmd_name);
	return (ret);
}
