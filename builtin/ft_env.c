/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:18:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/29 11:00:57 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_env(t_minishell *minishell)
{
	char	**ret;
	int		index;
	int		i;

	ret = ft_charenv(minishell->env, FALSE);
	index = -1;
	while (ret[++index])
	{
		i = -1;
		while (ret[index][++i])
		{
			if (ret[index][i] != '=')
				continue ;
		}
		printf("%s\n", ret[index]);
		free(ret[index]);
	}
	free(ret);
	ret = NULL;
	return (FUNC_SUC);
}
