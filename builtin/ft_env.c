/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:18:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/09 13:10:19 by minsepar         ###   ########.fr       */
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
		free(ret[index]);
	}
	free(ret);
	ret = NULL;
	return (FUNC_SUC);
}
