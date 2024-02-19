/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:17:16 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/19 11:55:43 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	process_builtin(t_cmd_node *cmd_node)
{
	char	*cmd_name;

	cmd_name = cmd_node->cmd_name;
	if (str_equal(cmd_name, "echo"))
		ft_echo(cmd_node);
	else if (str_equal(cmd_name, "cd"))
		ft_cd(cmd_node);
	else if (str_equal(cmd_name, "pwd"))
		ft_pwd(cmd_node);
	else if (str_equal(cmd_name, "export"))
		ft_export(cmd_node);
	else if (str_equal(cmd_name, "unset"))
		ft_unset(cmd_node);
	else if (str_equal(cmd_name, "env"))
		ft_env(cmd_node);
	else if (str_equal(cmd_name, "exit"))
		ft_exit(cmd_node);
}
