/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:05:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/07 22:28:50 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <asm-generic/fcntl.h>

void	parse_single_char(t_parse_str *parse_str, char **str)
{
	if (**str)
	{
		if (**str == '\\')
			(*str)++;
		else if (**str == '*')
			parse_str->asterisk_flag = 1;
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

static int	decode_ansi_c_str_helper(t_parse_str *parse_str, char **str)
{
	if (**str = '0')
}

int	decode_ansi_c_str(t_parse_str *parse_str, char **str)
{
	int return_status;

	return_status = 0;
	(*str)++;
	if (**str == 'a')
		append_char(parse_str, '\a');
	else if (**str == 'b')
		append_char(parse_str, '\b');
	else if (**str == 'e' || **str == 'E')
		append_char(parse_str, '\e');
	else if (**str == 'f')
		append_char(parse_str, '\f');
	else if (**str == 'n')
		append_char(parse_str, '\n');
	else if (**str == 'r')
		append_char(parse_str, '\r');
	else if (**str == 't')
		append_char(parse_str, '\t');
	else if (**str == 'v')
		append_char(parse_str, '\v');
	else
		return_status = decode_ansi_c_str_helper(parse_str, str);
}

void	parse_ansi_c_quote(t_parse_str *parse_str, char **str)
{
	int invalid_flag;

	invalid_flag = 0;
	(*str)++;
	while (**str && **str != '\'')
	{
		if (invalid_flag == FALSE && **str == '\\')
			decode_ansi_c_str(parse_str, str);
		if (invalid_flag == FALSE)
			append_char(parse_str, **str);
		(*str)++;
	}
}

void	parse_env_var(t_parse_str *parse_str, char **str)
{
	char	*env_name;
	char	*substitude_name;

	while (**str && !isspace(**str))
		parse_single_char(parse_str, str);
	env_name = ft_substr(parse_str->str, 0, parse_str->cursor);
	substitude_name = getenv(env_name);
	free(env_name);
	free(parse_str->str);
	parse_str->str = ft_strdup(substitude_name);
	parse_str->cursor = ft_strlen(substitude_name);
}

void	parse_dollar_sign(t_parse_str *parse_str, char **str)
{
	(*str)++;
	if (**str == '\"')
		parse_double_quote(parse_str, str);
	else if (**str == '\'')
		parse_ansi_c_quote(parse_str, str);
	else
		parse_env_var(parse_str, str);
}

void	get_cwd_files(t_str_list *str_list)
{
	struct dirent	*t_dirent;
	DIR				*dir;
	char			*cwd;

	cwd = getcwd(0, 0);
	dir = opendir(cwd);
	t_dirent = readdir(dir);
	while (t_dirent)
	{
		enqueue(str_list, create_node(t_dirent->d_name));
		t_dirent = readdir(dir);
	}
}

static void	is_match_init(t_inner_parser *inner_parser)
{
	inner_parser->i = 0;
	inner_parser->j = 0;
	inner_parser->start_index = -1;
	inner_parser->match = 0;
}

int	is_match_loop(t_inner_parser *info, char *pattern, char *file_name)
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

int	is_match(char *file_name, char *pattern)
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

void	pattern_not_found(t_str_list *str_list, char *pattern)
{
	t_str_node	*node;

	node = create_node(pattern);
	node->str = pattern;
	enqueue(str_list, node);
}

void	parse_asterisk(t_str_list *str_list, t_parse_str *parse_str)
{
	int		found_flag;
	t_str_list	dir_file_list;
	char		*pattern;
	t_str_node	*cur_node;

	found_flag = 0;
	init_str_list(&dir_file_list);
	get_cwd_files(&dir_file_list);
	pattern = parse_str->str;
	cur_node = dequeue(&dir_file_list);
	while (cur_node)
	{
		if (is_match(cur_node->str, pattern) == TRUE)
		{
			found_flag = 1;
			enqueue(str_list, cur_node);
		}
		else
			free(cur_node);
		cur_node = dequeue(&dir_file_list);
	}
	if (found_flag == FALSE)
		pattern_not_found(str_list, pattern);
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
	{
		if (parse_str.asterisk_flag == 1)
			parse_asterisk(str_list, &parse_str);
		else
			add_string_node(str_list, &parse_str);
	}
}

char	**string_parser(char *str)
{
	t_str_list	str_list;

	init_str_list(&str_list);
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		parse_single_word(&str, &str_list);
	}
	return (list_to_char_arr(&str_list));
}

int main(int argc, char **argv)
{
	t_str_list	str_list;
	t_str_node	*cur_node;
	t_parse_str	parse_str;

	init_str_list(&str_list);
	init_parse_str(&parse_str);
	parse_single_word(&argv[1], &str_list);
	while (str_list.size > 0)
	{
		cur_node = dequeue(&str_list);
		printf("here: %s\n", cur_node->str);
	}
//	char *str = "\x29\x29\x29\x29\n";
	
}
