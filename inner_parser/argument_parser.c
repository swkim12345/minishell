/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:05:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/05 21:02:28 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <fcntl.h>

void	parse_single_char(t_str_list *str_list, t_parse_str *parse_str, char **str,
		t_minishell *minishell)
{
	if (**str)
	{
		if (**str == '\\' && (*str)[1] == '\\')
			(*str) += 1;
		else if (**str == '\\' && (*str)[1] == '\0')
		{
			(*str)++;
			return ;
		}
		else if (**str == '\\')
			(*str)++;
		else if (parse_str->quote_flag == FALSE && **str == '*'
			&& parse_str->asterisk_flag == -1)
			parse_str->asterisk_flag = 1;
		else if (**str == '$')
		{
			parse_dollar_sign(str_list, parse_str, str, minishell);
			return ;
		}
		append_char(parse_str, **str);
		*str = *str + 1;
	}
}

void	parse_double_quote(t_str_list *str_list, t_parse_str *parse_str, char **str,
	t_minishell *minishell)
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

void	parse_single_quote(t_parse_str *parse_str, char **str)
{
	parse_str->quote_flag = 1;
	(*str)++;
	while (**str && **str != '\'')
	{
		parse_str->asterisk_flag = 0;
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

void	parse_env_var_found(t_str_list *str_list, t_parse_str *parse_str,
	char *substitude_name, int start_index)
{
	// ft_printf("[%s]\n", substitude_name);
	parse_str->cursor = start_index;
	if (parse_str->quote_flag)
	{
		while (*substitude_name)
		{
			append_char(parse_str, *substitude_name);
			substitude_name++;
		}
		
	}
	else
	{
		while (*substitude_name)
		{
			while (*substitude_name && ft_isspace(*substitude_name))
				substitude_name++;
			while (*substitude_name && !ft_isspace(*substitude_name))
			{
				append_char(parse_str, *substitude_name);
				substitude_name++;
			}
			if (*substitude_name)
			{
				add_string_node(str_list, parse_str);
				init_parse_str(parse_str);
			}
		}
	}
	//printf("parse_str: %s\n", parse_str->str);
}

void	parse_env_var(t_str_list *str_list, t_parse_str *parse_str,
	char **str, t_minishell *minishell)
{
	char	*env_name;
	char	*substitude_name;
	size_t		start_index;

	//ft_printf("dollar cur_char: [%c]\n", **str);
	start_index = parse_str->cursor;
	append_char(parse_str, '$');
	while (**str && !ft_isspace(**str) && (!parse_str->quote_flag || **str != '\"')
		&& **str != '$' && **str != '\"' && **str != '\'' && **str != '/')
		parse_single_char(str_list, parse_str, str, minishell);
	if (parse_str->cursor == start_index + 1)
		return ;
	env_name = ft_substr(parse_str->str, start_index + 1, parse_str->cursor);
	substitude_name = ft_getenv(minishell->env, env_name);
	//printf("find name: %s\n", env_name);
	//printf("found name: %s\n", substitude_name);
	//printf("env_name: %s\n", env_name);
	free(env_name);
	if (!substitude_name)
	{
		parse_str->cursor = start_index;
		parse_str->str[start_index] = 0;
		//printf("subname_null: %s\n", env_name);
		return ;
	}
	parse_env_var_found(str_list, parse_str, substitude_name, start_index);
}

void	parse_question_mark(t_parse_str *parse_str, char **str,
	t_minishell *minishell)
{
	char	*exit_status;
	int		i;

	exit_status = ft_itoa(minishell->exit_code);
	i = 0;
	while (exit_status[i])
	{
		append_char(parse_str, exit_status[i]);
		i++;
	}
	free(exit_status);
	(*str)++;
}

void	parse_dollar_sign(t_str_list *str_list, t_parse_str *parse_str, char **str, t_minishell *minishell)
{
	(*str)++;
	if (**str == '\"' && parse_str->quote_flag == FALSE)
		parse_double_quote(str_list, parse_str, str, minishell);
	else if (**str == '\'' && parse_str->quote_flag == FALSE)
		parse_single_quote(parse_str, str);
	else if (**str == '?')
		parse_question_mark(parse_str, str, minishell);
	else
		parse_env_var(str_list, parse_str, str, minishell);
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
		enqueue(str_list, create_node(ft_strdup(t_dirent->d_name)));
		t_dirent = readdir(dir);
	}
	free(cwd);
	closedir(dir);
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
		{
			free(cur_node->str);
			free(cur_node);
		}
		cur_node = dequeue(&dir_file_list);
	}
	if (found_flag == FALSE)
		pattern_not_found(str_list, pattern);
}

int	contains_assignment(char *str)
{
	while (*str)
	{
		//ft_printf("cur_char: [%c]\n", *str);
		if (*str == '=')
			return (1);
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
		}
		else if (*str == '\"')
		{
			str++;
			while (*str && *str != '\"')
				str++;
		}
		str++;
	}
	return (0);
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
	{
		//printf("contains assignment\n");
		parse_assignment(&parse_str, str);
	}
	while (**str && !ft_isspace(**str))
	{
		if (**str == '\"')
			parse_double_quote(str_list, &parse_str, str, minishell);
		else if (**str == '\'')
			parse_single_quote(&parse_str, str);
		else if (**str == '$')
			parse_dollar_sign(str_list, &parse_str, str, minishell);
		else
			parse_single_char(str_list, &parse_str, str, minishell);
		parse_str.quote_flag = 0;
	}
	if (parse_str.cursor > 0 || parse_str.quote_flag == 1)
	{
		if (parse_str.asterisk_flag == 1)
			parse_asterisk(str_list, &parse_str);
		else
			add_string_node(str_list, &parse_str);
	}
}

t_str_list	*string_to_str_list(char *str, t_minishell *minishell)
{
	t_str_list	*str_list;

	str_list = ft_calloc(1, sizeof(t_str_list));
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (!(*str))
			break ;
		parse_single_word(&str, str_list, minishell);
	}
	return (str_list);
}

char	**string_parser(char *str, t_minishell *minishell)
{
	t_str_list	*str_list;
	char		**str_arr;

	str_list = string_to_str_list(str, minishell);
	str_arr = list_to_char_arr(str_list);
	free(str_list);
	return (str_arr);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char **str;
// 	t_minishell minishell;
// 	// init_shell(&minishell, envp, argv);

// 	char *input_str = readline(0);
// 	str = string_parser(input_str, &minishell);
// 	int i = 0;
// 	printf("input_str: %s\n", input_str);
// 	while (str[i])
// 	{
// 		printf("parsed_str: [%s]\n", str[i]);
// 		i++;
// 	}
// }
