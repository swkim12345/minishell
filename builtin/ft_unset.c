/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/28 13:38:33 by sunghwki         ###   ########.fr       */
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
		if (!(ft_isalpha(cmd_node->str[index][i]) == TRUE && cmd_node->str[index][i] != '_'))
			return (print_error_msg(minishell->error, 1, FALSE));
		while (cmd_node->str[index][++i])
		{
			if (!(cmd_node->str[index][i] == '_') && ft_isalnum(cmd_node->str[index][i]))
				return (print_error_msg(minishell->error, 1, FALSE));
		}
		free_error(minishell->error);
		if (ft_unsetenv(minishell->export, cmd_node->str[index]) == FUNC_FAIL)
			return (FUNC_FAIL);
		if (ft_unsetenv(minishell->env, cmd_node->str[index]) == FUNC_FAIL)
			return (FUNC_FAIL);
	}
	return (FUNC_SUC);
}
