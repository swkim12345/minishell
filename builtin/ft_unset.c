/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/22 18:18:41 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_unset(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;
	int		ret;

	index = 0;
	while (cmd_node->str[++index])
	{
		minishell->error = set_error_msg(minishell->execute_name,
				cmd_node->cmd_name, cmd_node->str[index], "not a valid identifier");
		if (!ft_isalpha(cmd_node->str[index][0]))
			print_error_msg(minishell->error, 1, TRUE);
		ret = ft_unsetenv(minishell->export, cmd_node->str[index]);
		if (ret == FUNC_FAIL)
			return (FUNC_FAIL);
		ret = ft_unsetenv(minishell->env, cmd_node->str[index]);
		if (ret == FUNC_FAIL)
			return (FUNC_FAIL);
	}
	return (FUNC_SUC);
}
