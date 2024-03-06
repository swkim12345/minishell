/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:09:01 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/06 22:10:25 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	is_match_loop(t_inner_parser *info, char *pattern, char *file_name)
{
	if (pattern[info->j] && pattern[info->j] == file_name[info->i])
	{
		info->i++;
		info->j++;
	}
	else if (pattern[info->j] && pattern[info->j] == '*')
	{
		while (pattern[info->j + 1] && pattern[info->j + 1] == '*')
			info->j++;
		info->start_index = info->j;
		info->match = info->i;
		info->j++;
	}
	else if (info->start_index != -1)
	{
		info->j = info->start_index + 1;
		info->match++;
		info->i = info->match;
	}
	else
		return (FALSE);
	return (TRUE);
}

static void	is_match_init(t_inner_parser *inner_parser)
{
	inner_parser->i = 0;
	inner_parser->j = 0;
	inner_parser->start_index = -1;
	inner_parser->match = 0;
}

int	is_pattern_match(char *file_name, char *pattern)
{
	t_inner_parser	inner_parser;

	is_match_init(&inner_parser);
	if (pattern[0] != '.' && (file_name[0] == '.'
			|| (file_name[0] == '.' && file_name[1] == '.')))
		return (FALSE);
	while (file_name[inner_parser.i])
	{
		if (is_match_loop(&inner_parser, pattern, file_name) == FALSE)
			return (FALSE);
	}
	while (pattern[inner_parser.j] && pattern[inner_parser.j] == '*')
		inner_parser.j++;
	return (pattern[inner_parser.j] == file_name[inner_parser.i]);
}
