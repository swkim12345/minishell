/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:07:00 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/06 22:07:35 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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
