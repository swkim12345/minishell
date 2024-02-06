/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:16:31 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/06 23:51:49 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

long	find_bracket(char *input)
{
	long	index;

	index = 0;
	while (input[index])
	{
		if (!ft_strncmp(input[index], DOUBLEQUOT, 1) 
		|| !ft_strncmp(input[index], SINGLEQUOT, 1))
		{
			while (TRUE)
			{
				if (!ft_strncmp(input[index], DOUBLEQUOT, 1) 
				|| !ft_strncmp(input[index], SINGLEQUOT, 1))
					break;
				index++;
			}
		}
		if (!ft_strncmp(input[index], BRACKET[0], 1)
		|| !ft_strncmp(input[index], BRACKET[1], 1))
			break ;
		index++;
	}
	return (index);
}

long	find_or_and_bracket(char *input)
{
	long	index;

	index = 0;
	while (input[index])
	{
		if (!ft_strncmp(input[index], DOUBLEQUOT, 1) 
		|| !ft_strncmp(input[index], SINGLEQUOT, 1))
		{
			while (TRUE)
			{
				if (!ft_strncmp(input[index], DOUBLEQUOT, 1) 
				|| !ft_strncmp(input[index], SINGLEQUOT, 1))
					break;
				index++;
			}
		}
		if (!ft_strncmp(input[index], OR, 2))
			return (index);
		if (!ft_strncmp(input[index], AND, 2))
			return (index);
		if (!ft_strncmp(input[index], BRACKET[0], 1)
		|| !ft_strncmp(input[index], BRACKET[1], 1))
			return (index);
		index++;
	}
	return (index);
}

long	find_quot(char *input, int is_double)
{
	long index;
	char tmp;

	index = 0;
	if (is_double == FALSE)
		tmp = SINGLEQUOT[0];
	else
		tmp = DOUBLEQUOT[0];
	while (input[index])
	{
		if (!ft_strncmp(input[index], &tmp, 1))
			break;
		index++;
	}
	return (index);
}
