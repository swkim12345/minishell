/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:24:42 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/14 20:33:45 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

long	parser_redirect(t_cmd_node *leaf, long start)
{
	long	index;
	char	*ptr;
	char	*new_str;
	char	*new_node_str;

	ptr = leaf->str[0];
	index = start + 1;
	if (!ft_strncmp(&ptr[index], &ptr[start], 1))
		index++;
	index += skip_space(&ptr[index]);
	while (ptr[index])
	{
		if (ptr[index] == ' ' || ptr[index] == '>' || ptr[index] == '<')
			break ;
		index++;
	}
	new_str = (char *)malloc(sizeof(char) * (index - start + 1));
	new_str[index - start] = '\0';
	ft_memmove((void *)new_str, (void *)&ptr[start], index - start);
	if (leaf->redirect)
	{
		new_node_str = ft_strjoin(leaf->redirect, new_str);
		free(leaf->redirect);
		leaf->redirect = new_node_str;
	}
	else
		leaf->redirect = new_str;
	ptr[start] = '\0';
	ptr[index - 1] = '\0';
	new_node_str = ft_strjoin(&ptr[0], &ptr[index]);
	free_doub_char(leaf->str);
	leaf->str = init_doub_char(&new_node_str, 1);
	return (0);
}

t_cmd_node	*parser(t_cmd_node *leaf)
{
	char	*ptr;
	char	*str;
	long	index;

	ptr = leaf->str[0];
	index = 0;
	while (ptr[index])
	{
		if (!str_cmp(&ptr[index], SINGLEQUOT) ||
		!str_cmp(&ptr[index], DOUBLEQUOT))
			index += find_end_quote(&ptr[index]);
		if (!str_cmp(&ptr[index], &BRACKET[0]))
			index += find_bracket(&ptr[index]);
		if (!str_cmp(&ptr[index], REDIRINPUT) ||
		!str_cmp(&ptr[index], REDIROUTPUT))
		{
			index = parser_redirect(leaf, index);
			continue ;
		}
		if (!ptr[index])
			break ; //에러 처리 필요
		index++;
	}
	return (leaf);
}
