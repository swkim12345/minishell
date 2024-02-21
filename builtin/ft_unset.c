/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/21 17:21:12 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int			ft_unset(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;
	int		ret;

	index = 0;
	while (cmd_node->str[++index])
	{
		if (!ft_isalpha(cmd_node->str[index][0]))
			return (err_msg(minishell->execute_name, cmd_node->str[0],
			 cmd_node->str[index], "not a valid identifier"));
		ret = ft_unsetexport(&minishell->export, cmd_node->str[index]);
		if (ret == FUNC_FAIL)
			return (FUNC_FAIL);
		ret = ft_unsetenv(&minishell->env, cmd_node->str[index]);
		if (ret == FUNC_FAIL)
			return (FUNC_FAIL);
	}
	return (FUNC_SUC);
}
