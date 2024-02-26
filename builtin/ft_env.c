/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:18:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/26 20:17:18 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_env(t_cmd_node *cmd_node, t_minishell *minishell)
{
	char	**ret;
	int		index;
	(void) cmd_node;

	ret = ft_charenv(minishell->env, FALSE);
	index = -1;
	while (ret[++index])
	{
		printf("%s\n", ret[index]);
		free(ret[index]);
	}
	free(ret);
	ret = NULL;
	return (FUNC_SUC);
}
