/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:25:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/13 16:40:09 by sunghwki         ###   ########.fr       */
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

// int	traverse(t_ast_node *head)
// {
// 	ret = (t_ast_list *)malloc(sizeof(t_ast_list));
// 	ret->next = NULL;
// 	tmp = ret;
// 	//leaf node
// 	if (head->cmd_node)
// 	{
// 		//execution
// 		ret->node = head;
// 		return (ret);
// 	}
// 	//left tree inorder traverse
// 	if (head->left_node)
// 	{
// 		ret->next = traverse(head->left_node);
// 		tmp = find_end(ret);
// 	}
// 	//right tree inorder traverse
// 	ret->next = traverse(head->right_node);
// 	return (TRUE);
// }
