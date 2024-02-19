/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 23:44:33 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/19 11:52:20 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	str_cmp(char *str_org, char *str_cmp)
{
	while (*str_org && *str_cmp && *str_org == *str_cmp)
	{
		str_org++;
		str_cmp++;
	}
	if (!*str_cmp)
		return (0);
	return (*str_org - *str_cmp);
}
