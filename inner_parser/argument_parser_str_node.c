/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser_str_node.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:25:42 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 15:46:20 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_str_node	*create_node(char *str)
{
	t_str_node	*str_node;

	str_node = (t_str_node *)ft_calloc(sizeof(t_str_node), 1);
	str_node->str = str;
	str_node->next = 0;
	str_node->flag = 0;
	return (str_node);
}

void	free_str_node(t_str_node *str_node)
{
	free(str_node->str);
	free(str_node);
}
