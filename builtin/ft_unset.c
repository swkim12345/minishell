/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/28 12:52:33 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_unset(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;

	index = 0;
	while (cmd_node->str[++index])
	{
		minishell->error = set_error_msg(minishell->execute_name,
				cmd_node->cmd_name,
				cmd_node->str[index], "not a valid identifier");
		if (!ft_isalpha(cmd_node->str[index][0]))
			print_error_msg(minishell->error, 1, TRUE);
		// free_error(minishell->error);
		if (ft_unsetenv(minishell->export, cmd_node->str[index]) == FUNC_FAIL)
			return (FUNC_FAIL);
		if (ft_unsetenv(minishell->env, cmd_node->str[index]) == FUNC_FAIL)
			return (FUNC_FAIL);
	}
	return (FUNC_SUC);
}
