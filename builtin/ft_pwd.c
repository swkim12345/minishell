/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:50:45 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/16 13:00:23 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_pwd(t_cmd_node *node, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (node->str[1])
	{
		if (node->str[1][0] != '-')
		{
			printf("pwd: too many arguments\n");
			return (FUNC_FAIL);
		}
		if (node->str[1][0] == '-' && node->str[1][1])
		{
			if (node->str[1][1] == '-')
				i += 1;
			printf("pwd: bad option: %s\n", &node->str[1][i]);
			return (FUNC_FAIL);
		}
	}
	printf("%s\n", minishell->cwd);
	return (FUNC_SUC);
}
