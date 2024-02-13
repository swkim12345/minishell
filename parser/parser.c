/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:52:54 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/13 16:31:41 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	**parser(char *input)
{
	long	index;
	t_str_list	*str_list;
	t_str_node	*node;
	char	*ptr;
	char	**ret;

	index = 0;
	str_list = (t_str_list *)malloc(sizeof(t_str_list));
	init_str_list(str_list);
	while (input[index])
	{
		if (str_cmp(&input[index], SINGLEQUOT) || str_cmp(&input[index], DOUBLEQUOT))
			{
				index += find_end_quote(&input[index]);
				if (!input[index])
					return (NULL);
			}
		if (str_cmp(&input[index], " "))
		{
			ptr = ft_strtok(&input[index], " ");
			node = (t_str_node *)malloc(sizeof(t_str_node));
			init_str_node(node);
			node->str = ft_strdup(&input[index]);
			index = ptr - &input[index];
			enqueue(str_list, node);
		}
		index++;
	}
	ret = list_to_char_arr(str_list);
	printf("ret : %s", ret[0]);
	return (ret);
}
