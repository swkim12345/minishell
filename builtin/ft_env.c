/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:18:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/21 16:37:14 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int			ft_env(t_cmd_node *cmd_node, t_minishell *minishell)
{
	char	**ret;
	int		index;

	ret = tree_to_char(minishell->env);
	index = -1;
	while (ret[++index])
	{
		printf("%s\n", ret[index]);
		free(ret[index]);
	}
	free(ret);
	return (FUNC_SUC);
}
