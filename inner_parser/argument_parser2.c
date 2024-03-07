/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:59:42 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 15:23:37 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	parse_double_quote(t_str_list *str_list, t_parse_str *parse_str,
			char **str, t_minishell *minishell)
{
	parse_str->quote_flag = 1;
	(*str)++;
	while (**str && **str != '\"')
	{
		parse_str->asterisk_flag = 0;
		parse_single_char(str_list, parse_str, str, minishell);
	}
	(*str)++;
}

static void	pattern_not_found(t_str_list *str_list, char *pattern)
{
	t_str_node	*node;

	node = create_node(pattern);
	node->str = ft_strdup(pattern);
	enqueue(str_list, node);
}

void	parse_asterisk(t_str_list *str_list, t_parse_str *parse_str)
{
	int			found_flag;
	t_str_list	dir_file_list;
	char		*pattern;
	t_str_node	*cur_node;

	found_flag = 0;
	ft_memset(&dir_file_list, 0, sizeof(t_str_list));
	get_cwd_files(&dir_file_list);
	pattern = parse_str->str;
	cur_node = dequeue(&dir_file_list);
	while (cur_node)
	{
		if (is_pattern_match(cur_node->str, pattern) == TRUE)
		{
			found_flag = 1;
			enqueue(str_list, cur_node);
		}
		else
			free_str_node(cur_node);
		cur_node = dequeue(&dir_file_list);
	}
	if (found_flag == FALSE)
		pattern_not_found(str_list, pattern);
}

void	parse_assignment(t_parse_str *parse_str, char **str)
{
	while (**str && !ft_isspace(**str))
	{
		if (**str == '\'')
		{
			append_char(parse_str, **str);
			(*str)++;
			while (**str && **str != '\'')
			{
				append_char(parse_str, **str);
				(*str)++;
			}
		}
		else if (**str == '\"')
		{
			append_char(parse_str, **str);
			(*str)++;
			while (**str && **str != '\"')
			{
				append_char(parse_str, **str);
				(*str)++;
			}
		}
		append_char(parse_str, **str);
		(*str)++;
	}
}

void	parse_single_word(char **str, t_str_list *str_list,
	t_minishell *minishell)
{
	t_parse_str	parse_str;

	init_parse_str(&parse_str);
	if (contains_assignment(*str) == TRUE)
		parse_assignment(&parse_str, str);
	while (**str && !ft_isspace(**str))
	{
		parse_str.quote_flag = 0;
		if (**str == '\"')
			parse_double_quote(str_list, &parse_str, str, minishell);
		else if (**str == '\'')
			parse_single_quote(&parse_str, str);
		else if (**str == '$')
			parse_dollar_sign(str_list, &parse_str, str, minishell);
		else
			parse_single_char(str_list, &parse_str, str, minishell);
	}
	if (parse_str.cursor > 0 || parse_str.quote_flag == 1)
	{
		if (parse_str.asterisk_flag == 1)
			parse_asterisk(str_list, &parse_str);
		else
			add_string_node(str_list, &parse_str);
	}
	free_parse_str(&parse_str);
}
