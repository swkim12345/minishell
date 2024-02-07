/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:01:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/07 16:32:28 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

long	find_bracket(char *input)
{
	long	index;
	char	c;

	index = 0;
	while (input[index])
	{
		if (!ft_strncmp(input[index], DOUBLEQUOT, 1)
			|| !ft_strncmp(input[index], SINGLEQUOT, 1))
		{
			c = input[index];
			while (input[++index])
			{
				if (!ft_strncmp(input[index], &c, 1))
					break ;
			}
		}
		if (!ft_strncmp(input[index], BRACKET[0], 1)
			|| !ft_strncmp(input[index], BRACKET[1], 1))
			break ;
		index++;
	}
	return (index);
}

long	find_quot(char *input, int is_double)
{
	long	index;
	char	tmp;

	index = 0;
	if (is_double == FALSE)
		tmp = SINGLEQUOT[0];
	else
		tmp = DOUBLEQUOT[0];
	while (input[index])
	{
		if (!ft_strncmp(input[index], &tmp, 1))
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
					break ;
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
