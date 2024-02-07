/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:05:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/07 22:17:16 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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

// void	parse_dollar_sign(t_parse_str *parse_str, char **str)
// {
// 	(*str)++;
// 	if (**str == )
// }

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

int	recursive_match(char *file_name, char *pattern)
{
	if ((!*file_name && *pattern == '*' && *(pattern + 1) == '\0') || !*pattern)
		return (TRUE);
	else if (!*file_name)
		return (FALSE);
	if (*pattern != '*')
	{
		if (*file_name && *pattern && *file_name == *pattern)
		{
			file_name++;
			pattern++;
		}
		else
			return (FALSE);
	}
	else
	{
		recursive_match(file_name, pattern + 1);
		while (*file_name)
		{
			file_name++;
			if (recursive_match(file_name, pattern))
				return (TRUE);
		}
	}
	return (FALSE);
}

void	parse_asterisk(t_str_list *str_list, t_parse_str *parse_str)
{
	t_str_list	dir_file_list;

	get_cwd_files(&dir_file_list);
	
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
		// else if (**str == '$')
		// 	parse_dollar_sign(&parse_str, str);
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
	int boolean = recursive_match(argv[1], argv[2]);
	if (boolean)
		printf("true\n");
	else
		printf("false\n");
}