/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:25:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/13 20:20:39 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

//traverse left node first, return next execution or null(error)
//left first, 
// t_ast_list	*find_end(t_ast_list *node)
// {
// 	t_ast_list	*ret;
	
// 	ret = node;
// 	while (ret->next)
// 		ret = node->next;
// 	return (ret);
// }
//check or / and
int	traverse(t_ast_node *head)
{
	int	ret;

	if (!head)
		return (TRUE);
	ret = traverse(head->left_node);
	if (head->cmd_node)
		// return (process_command(head->cmd_node));
	{
		printf("cmd_node : %s\n", head->cmd_node->str[0]);
		return (TRUE);
	}
	if (head->str)
		printf("str : %s\n", head->str);
	if ((str_cmp(head->str, AND) && ret) ||
	(str_cmp(head->str, OR) && !ret))
		ret = traverse(head->right_node);
	return (ret);
}
