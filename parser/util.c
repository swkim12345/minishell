/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 23:44:33 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/13 17:48:27 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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