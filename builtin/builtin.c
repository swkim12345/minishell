/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:17:16 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/25 15:58:09 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	process_builtin(t_cmd_node *cmd_node, t_minishell *minishell)
{
	char	*cmd_name;
	int		ret;

	cmd_name = cmd_node->cmd_name;
	ret = FUNC_SUC;
	if (str_equal(cmd_name, "echo"))
		ret = ft_echo(cmd_node);
	else if (str_equal(cmd_name, "cd"))
		ret = ft_cd(cmd_node, minishell);
	else if (str_equal(cmd_name, "pwd"))
		ret = ft_pwd(cmd_node, minishell);
	else if (str_equal(cmd_name, "export"))
		ret = ft_export(cmd_node, minishell);
	else if (str_equal(cmd_name, "unset"))
		ret = ft_unset(cmd_node, minishell);
	else if (str_equal(cmd_name, "env"))
		ret = ft_env(cmd_node);
	else if (str_equal(cmd_name, "exit"))
		ret = ft_exit(cmd_node);
	return (ret);
}
