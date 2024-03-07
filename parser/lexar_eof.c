/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_eof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:13:42 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/07 20:14:54 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*eof_parser(char *ptr)
{
	t_parse_str	parse_str;
	char		*ret;
	int			flag;
	int			index;

	init_parse_str(&parse_str);
	index = -1;
	while (ptr[++index])
	{
		if (ptr[index] == '\"' || ptr[index] == '\'')
		{
			flag = ptr[index];
			index++;
			while (ptr[index] != flag)
			{
				append_char(&parse_str, ptr[index]);
				index++;
			}
			continue ;
		}
		if (ft_isspace(ptr[index]) == TRUE)
			continue ;
		append_char(&parse_str, ptr[index]);
	}
	ret = ft_strdup(parse_str.str);
	free_parse_str(&parse_str);
	free(ptr);
	return (ret);
}
