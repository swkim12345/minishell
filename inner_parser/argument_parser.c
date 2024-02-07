/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:05:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/07 15:40:30 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	parse_single_char(t_parse_str *parse_str, char **str)
{
	if (**str)
	{
		if (**str == '\\')
			(*str)++;
		append_char(parse_str, **str);
		*str = *str + 1;
	}
}

void	parse_double_quote(t_parse_str *parse_str, char **str)
{
	(*str)++;
	while (**str && **str != '\"')
		parse_single_char(parse_str, str);
	(*str)++;
}

void	parse_single_quote(t_parse_str *parse_str, char **str)
{
	(*str)++;
	while (**str && **str != '\'')
	{
		parse_single_char(parse_str, str);
	}
	(*str)++;
}

void	parse_dollar_sign(t_parse_str *parse_str, char **str)
{
	(*str)++;
	if (**str == )
}

void	parse_single_word(char **str, t_str_list *str_list)
{
	t_parse_str	parse_str;

	init_parse_str(&parse_str);
	while (**str && !ft_isspace(**str))
	{
		if (**str == '\"')
			parse_double_quote(&parse_str, str);
		else if (**str == '\'')
			parse_single_quote(&parse_str, str);
		else if (**str == '$')
			parse_dollar_sign(&parse_str, str);
		else
			parse_single_char(&parse_str, str);
	}
	if (parse_str.cursor > 0)
		add_string_node(str_list, &parse_str);
}
