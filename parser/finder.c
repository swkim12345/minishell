/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:01:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/19 15:37:33 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	long	bracket_counter;
	char	c;

	index = 0;
	if (!str_cmp(&input[index], &BRACKET[0]))
		return (index);
	bracket_counter = 1;
	while (input[++index])
	{
		if (!str_cmp(&input[index], SINGLEQUOT) ||
		!str_cmp(&input[index], DOUBLEQUOT))
			index += find_end_quote(&input[index]);
		if (!ft_strncmp(&input[index], &BRACKET[0], 1))
			bracket_counter++;
		if (!ft_strncmp(&input[index], &BRACKET[1], 1))
			bracket_counter--;
		if (bracket_counter == 0)
			return (index);
		if (!input[index])
			break ;
	}
	if (bracket_counter != 0)
		return (-1);
	return (index);
}

long	find_pipe(char *input)
{
	long	index;
	char	c;

	index = -1;
	while (input[++index])
	{
		if (!str_cmp(&input[index], SINGLEQUOT) ||
		!str_cmp(&input[index], DOUBLEQUOT))
			index += find_end_quote(&input[index]);
		if (!str_cmp(&input[index], &BRACKET[0]))
			index += find_bracket(&input[index]);
		if (!str_cmp(&input[index], OR))
		{
			index += 2;
			continue ;
		}
		if (!str_cmp(&input[index], PIPE))
			break ;
		if (!input[index])
			break ;
	}
	return (index);
}

long	find_or_and(char *input, t_ast_node *head)
{
	long	index;
	long	error_check;
	char	c;

	index = -1;
	while (input[++index])
	{
		if (!str_cmp(&input[index], SINGLEQUOT) ||
		!str_cmp(&input[index], DOUBLEQUOT))
			index += find_end_quote(&input[index]);
		if (!ft_strncmp(&input[index], &BRACKET[0], 1))
		{
			printf("find bracket\n");
			error_check = find_bracket(&input[index]);
			if (error_check < 0)
				return (-1);
			index += error_check;
			head->flag |= BRACKET_FLAG;
		}
		if (!str_cmp(&input[index], OR))
			break ;
		if (!str_cmp(&input[index], AND))
			break ;
		if (!input[index])
			break ;
	}
	return (index);
}

long	skip_space(char *input)
{
	long	index;

	index = -1;
	while (input[++index])
	{
		if (input[index] != ' ')
			break ;
	}
	return (index);
}
