/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser_str_list2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:09:40 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/09 12:49:17 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_str_stack(t_str_list *stack)
{
	t_str_node	*cur_node;

	while (stack->size > 0)
	{
		cur_node = pop(stack);
		free(cur_node->str);
		free(cur_node);
	}
}

char	*stack_to_str(t_str_list *stack)
{
	int			i;
	t_str_node	*cur_node;
	t_parse_str	parse_str;
	char		*return_str;

	init_parse_str(&parse_str);
	cur_node = stack->head;
	while (cur_node)
	{
		i = -1;
		while (cur_node->str[++i])
			append_char(&parse_str, cur_node->str[i]);
		cur_node = cur_node->next;
	}
	free(return_str);
	return_str = ft_substr(parse_str.str, 0, parse_str.cursor);
	free(parse_str.str);
	return (return_str);
}

char	*stack_to_str_free(t_str_list *stack)
{
	char	*return_str;

	return_str = stack_to_str(stack);
	free_str_stack(stack);
	return (return_str);
}
