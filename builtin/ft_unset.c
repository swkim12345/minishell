/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/29 13:43:19 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	ft_not_unset(t_cmd_node *cmd_node, t_minishell *minishell,
	int index)
{
	int	i;

	i = 0;
	minishell->error = set_error_msg(minishell->execute_name,
			cmd_node->cmd_name, cmd_node->str[index], "not a valid identifier");
	if (!(ft_isalpha(cmd_node->str[index][i]) == TRUE
		|| cmd_node->str[index][i] == '_'))
	{
		print_error_msg(minishell->error, 1, FALSE);
		return (FUNC_FAIL);
	}
	while (cmd_node->str[index][++i])
	{
		if (!(cmd_node->str[index][i] == '_'
			|| ft_isalnum(cmd_node->str[index][i])))
		{
			print_error_msg(minishell->error, 1, FALSE);
			return (FUNC_FAIL);
		}
	}
	free_error(minishell->error);
	return (FUNC_SUC);
}

int	ft_unset(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;

	index = 0;
	while (cmd_node->str[++index])
	{
		if (ft_not_unset(cmd_node, minishell, index) == FUNC_FAIL)
			continue ;
		ft_unsetenv(minishell->export, cmd_node->str[index]);
		ft_unsetenv(minishell->env, cmd_node->str[index]);
	}
	return (FUNC_SUC);
}
