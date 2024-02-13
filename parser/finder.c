/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:01:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/13 21:34:03 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

long	find_end_quote(char *input)
{
	long	index;
	char	c;

	index = 0;
	c = input[0];
	while (input[++index])
	{
		if (input[index] == c)
			return (index);
	}
	return (FALSE);
}

long	find_bracket(char *input)
{
	long	index;
	char	c;

	index = 0;
	while (input[index])
	{
		if (!str_cmp(&input[index], SINGLEQUOT) ||
		!str_cmp(&input[index], DOUBLEQUOT))
			index += find_end_quote(&input[index]);
		if (str_cmp(&input[index], &BRACKET[0])
			|| str_cmp(&input[index], &BRACKET[1]))
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
		if (!str_cmp(&input[index], SINGLEQUOT) ||
		!str_cmp(&input[index], DOUBLEQUOT))
			index += find_end_quote(&input[index]);
		if (!str_cmp(&input[index], OR))
		{
			index += 2;
			continue ;
		}
		if (!str_cmp(&input[index], PIPE))
			break ;
		if (!input[index])
			break ;
		index++;
	}
	return (index);
}

long	find_or_and(char *input)
{
	long	index;
	char	c;

	index = -1;
	while (input[++index])
	{
		if (!str_cmp(&input[index], SINGLEQUOT) ||
		!str_cmp(&input[index], DOUBLEQUOT))
			index += find_end_quote(&input[index]);
		if (!str_cmp(&input[index], OR))
			break ;
		if (!str_cmp(&input[index], AND))
			break ;
		if (!input[index])
			break ;
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
		if (!str_cmp(&input[index], SINGLEQUOT) ||
		!str_cmp(&input[index], DOUBLEQUOT))
			index += find_end_quote(&input[index]);
		index++;
	}
	return (index);
}
