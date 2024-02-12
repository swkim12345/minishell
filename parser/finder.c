/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:01:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/12 20:59:47 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

long	find_quot(char *input, int is_double)
{
	long	index;
	char	c;

	index = 0;
	if (is_double == FALSE)
		c = SINGLEQUOT[0];
	else
		c = DOUBLEQUOT[0];
	while (input[index])
	{
		if (!ft_strncmp(&input[index], &c, 1))
			break ;
		index++;
	}
	return (index);
}

long	find_end_quote(char *input)
{
	long	index;
	char	c;

	index = 0;
	while (input[index])
	{
		if (!ft_strncmp(&input[index], DOUBLEQUOT, 1)
			|| !ft_strncmp(&input[index], SINGLEQUOT, 1))
		{
			c = input[index];
			while (input[++index])
			{
				if (!ft_strncmp(&input[index], &c, 1))
					break ;
			}
		}
	}
	return (index);
}

long	find_bracket(char *input)
{
	long	index;
	char	c;

	index = 0;
	while (input[index])
	{
		index = find_end_quote(input);
		if (!input[index])
			return (index);
		if (!ft_strncmp(&input[index], &BRACKET[0], 1)
			|| !ft_strncmp(&input[index], &BRACKET[1], 1))
			break ;
		if (!input[index])
			break ;
		index++;
	}
	return (index);
}

long	find_pipe(char *input)
{
	long	index;
	char	c;

	index = 0;
	while (input[index])
	{
		index = find_end_quote(input);
		if (!input[index])
			return (index);
		if (!ft_strncmp(&input[index], PIPE, 1)
			&& ft_strncmp(&input[index], OR, 2))
			break ;
		if (!input[index])
			break ;
		index++;
	}
	return (index);
}

long	find_or_and_bracket(char *input)
{
	long	index;
	char	c;

	index = 0;
	while (input[index])
	{
		index = find_end_quote(input);
		if (!input[index])
			return (index);
		if (!ft_strncmp(&input[index], OR, 2))
			return (index);
		if (!ft_strncmp(&input[index], AND, 2))
			return (index);
		if (!ft_strncmp(&input[index], &BRACKET[0], 1)
			|| !ft_strncmp(&input[index], &BRACKET[1], 1))
			return (index);
		if (!input[index])
			break ;
		index++;
	}
	return (index);
}

long	find_redirect(char *input)
{
	long	index;
	char	c;

	index = 0;
	while (input[index])
	{
		index = find_end_quote(input);
		if (!input[index])
			return (index);
		if (!ft_strncmp(&input[index], OR, 2))
			return (index);
		if (!ft_strncmp(&input[index], AND, 2))
			return (index);
		if (!ft_strncmp(&input[index], &BRACKET[0], 1)
			|| !ft_strncmp(&input[index], &BRACKET[1], 1))
			return (index);
		if (!input[index])
			break ;
		index++;
	}
	return (index);
}
