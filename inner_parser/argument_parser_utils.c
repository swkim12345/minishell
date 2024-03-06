/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:03:58 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/06 22:03:02 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_parse_str(t_parse_str *parse_str)
{
	free(parse_str->str);
	parse_str->str = 0;
}

void	init_parse_str(t_parse_str *parse_str)
{
	ft_memset((void *)(parse_str), 0, sizeof(t_parse_str));
	parse_str->str = ft_calloc(sizeof(char), 11);
	parse_str->malloc_size = 10;
	parse_str->asterisk_flag = -1;
}

void	append_char(t_parse_str *parse_str, char c)
{
	char	*new_malloc;
	int		prev_size;

	if (parse_str->malloc_size == parse_str->cursor)
	{
		prev_size = parse_str->cursor;
		parse_str->malloc_size *= 2;
		new_malloc = malloc(parse_str->malloc_size + 1);
		while (prev_size--)
			new_malloc[prev_size] = parse_str->str[prev_size];
		free(parse_str->str);
		parse_str->str = new_malloc;
	}
	parse_str->str[parse_str->cursor] = c;
	parse_str->cursor++;
	parse_str->str[parse_str->cursor] = 0;
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
