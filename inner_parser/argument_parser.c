/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:05:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/13 16:56:53 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <fcntl.h>

void	parse_single_char(t_parse_str *parse_str, char **str, int in_quote)
{
	if (**str)
	{
		if (**str == '\\' && (*str)[1] == '\\')
			(*str) += 1;
		else if (**str == '\\')
			(*str)++;
		else if (in_quote == FALSE && **str == '*')
			parse_str->asterisk_flag = 1;
		else if (**str == '$')
		{
			parse_dollar_sign(parse_str, str, in_quote);
			return ;
		}
		append_char(parse_str, **str);
		*str = *str + 1;
	}
}

void	parse_double_quote(t_parse_str *parse_str, char **str)
{
	(*str)++;
	while (**str && **str != '\"')
		parse_single_char(parse_str, str, 1);
	(*str)++;
}

void	parse_single_quote(t_parse_str *parse_str, char **str)
{
	(*str)++;
	while (**str && **str != '\'')
	{
		append_char(parse_str, **str);
		(*str)++;
	}
	(*str)++;
}

char	*easy_cat(char *s1, char *s2)
{
	char	*return_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s1_copy;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s1_copy = s1_len;
	return_str = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	return_str[s1_len + s2_len] = 0;
	while (s1_len > 0)
	{
		s1_len--;
		return_str[s1_len] = s1[s1_len];
	}
	while (s2_len > 0)
	{
		s2_len--;
		return_str[s1_copy + s2_len] = s2[s2_len];
	}
	return (return_str);
}

void	parse_env_var_found(t_parse_str *parse_str, int in_quote,
	char *substitude_name, int start_index)
{
	int	i;

	i = 0;
	parse_str->cursor = start_index;
	while (*substitude_name)
	{
		append_char(parse_str, *substitude_name);
		substitude_name++;
	}
	printf("parse_str: %s\n", parse_str->str);
}

void	parse_env_var(t_parse_str *parse_str, char **str, int in_quote)
{
	char	*env_name;
	char	*substitude_name;
	int		start_index;

	printf("dollar cur_char: [%c]\n", **str);
	start_index = parse_str->cursor;
	while (**str && !isspace(**str) && (!in_quote || **str != '\"')
		&& **str != '$')
		parse_single_char(parse_str, str, 0);
	env_name = ft_substr(parse_str->str, start_index, parse_str->cursor);
	substitude_name = getenv(env_name);
	printf("find name: %s\n", env_name);
	printf("found name: %s\n", substitude_name);
	free(env_name);
	if (!substitude_name)
	{
		parse_str->cursor = start_index;
		parse_str->str[start_index] = 0;
		printf("subname_null: %s\n", env_name);
		if (in_quote == TRUE && **str == '$')
		{
			append_char(parse_str, '$');
			return ;
		}
		return ;
	}
	parse_env_var_found(parse_str, in_quote, substitude_name, start_index);
}

void	parse_dollar_sign(t_parse_str *parse_str, char **str, int in_quote)
{
	(*str)++;
	if (**str == '\"' && in_quote == FALSE)
		parse_double_quote(parse_str, str);
	else
		parse_env_var(parse_str, str, in_quote);
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
	int			found_flag;
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
			parse_dollar_sign(&parse_str, str, 0);
		else
			parse_single_char(&parse_str, str, 0);
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
	char **str;

	char *input_str = readline(0);
	str = string_parser(input_str);
	int i = 0;
	printf("input_str: %s\n", input_str);
	while (str[i])
	{
		printf("parsed_str: [%s]\n", str[i]);
		i++;
	}
}
