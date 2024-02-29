/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/29 10:57:51 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_unset(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;
	int		i;

	index = 0;
	while (cmd_node->str[++index])
	{
		minishell->error = set_error_msg(minishell->execute_name,
				cmd_node->cmd_name,
				cmd_node->str[index], "not a valid identifier");
		i = 0;
		if (!(ft_isalpha(cmd_node->str[index][i]) == TRUE || cmd_node->str[index][i] == '_'))
		{
			print_error_msg(minishell->error, 1, FALSE);
			continue ;
		}
		while (cmd_node->str[index][++i])
		{
			if (!(cmd_node->str[index][i] == '_' || ft_isalnum(cmd_node->str[index][i])))
			{
				print_error_msg(minishell->error, 1, FALSE);
				continue ;
			}
		}
		free_error(minishell->error);
		ft_unsetenv(minishell->export, cmd_node->str[index]);
		ft_unsetenv(minishell->env, cmd_node->str[index]);
	}
	return (FUNC_SUC);
}
