/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:45:22 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/29 16:43:23 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	str_equal(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (!*s1 && !*s2)
		return (1);
	return (0);
}

int		ft_isspace(int c)
{
	if (c >= 9 && c <= 12)
		return (1);
	if (c == 32)
		return (1);
	return (0);
}

char	*to_lowercase_str(const char *str)
{
	char	*return_str;
	int		i;

	i = 0;
	return_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		return_str[i] = str[i];
		i++;
	}
	return_str[i] = 0;
	return (return_str);
}

void	free_2d_str(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr[i]);
	free(arr);
}

void	clear_tmp_list(t_tmp_list *list, t_minishell *minishell)
{
	t_tmp_file	*cur;
	t_tmp_file	*next;

	cur = list->head;
	list->head = NULL;
	list->tail = NULL;
	while (cur)
	{
		next = cur->next;
		free(cur->tmp);
		free(cur);
		cur = next;
	}
	minishell->tmp_file_counter = 0;
}

void	free_tmp_list(t_tmp_list *list, t_minishell *minishell)
{
	clear_tmp_list(list, minishell);
	free(list);
	list = 0;
}
