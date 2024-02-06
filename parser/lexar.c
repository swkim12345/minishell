/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:28:22 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/06 22:16:44 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../main.h"

t_ast_node	*init_ast_node(int child_node)
{
	t_ast_node	*ret;
	t_list_node	*node;
	
	ret = (t_ast_node *)malloc(sizeof(t_ast_node));
	ft_memset((void *)ret, 0, sizeof(ret));
	if (CMD_NODE & child_node)
	{
		node = (t_ast_node *)malloc(sizeof(t_ast_node));
		ft_memset((void *)node, 0, sizeof(node));
		ret->cmd_node = node;
	}
	if (LEFT_NODE & child_node)
		ret->left_node = init_ast_node(CMD_NODE);
	if (RIGHT_NODE & child_node)
		ret->right_node = init_ast_node(CMD_NODE);
	return (ret);
}

long	find_or_and_bracket(char *input)
{
	long	index;

	index = 0;
	while (input[index])
	{
		if (!ft_strncmp(input[index], DOUBLEQUOT, 1) 
		|| !strncmp(input[index], SINGLEQUOT, 1))
		{
			while (TRUE)
			{
				if (!ft_strncmp(input[index], DOUBLEQUOT, 1) 
				|| !ft_strncmp(input[index], SINGLEQUOT, 1))
					break;
				index++;
			}
		}
		if (!strncmp(input[index], OR, 2))
			return (index);
		if (!strncmp(input[index], AND, 2))
			return (index);
		if (!strncmp(input[index], BRACKET[0], 1)
		|| !strncmp(input[index], BRACKET[1], 1))
			return (index);
		index++;
	}
	return (index);
}
 
t_ast_node	*recur_lexar(t_ast_node *head)
{
	t_ast_node	*ret;
	char		*str;
	long		index;
	
	//|| && check -> no -> return head
	if (!find_or_and_bracket(head->cmd_node->str))
		return (head);
	index = 0;
	while (head->cmd_node->str[index])
	{
		//|| && -> left child
		index = find_or_and_bracket(head->cmd_node->str);
		if (ft_strncmp)
		ret = init_ast_node(CMD_NODE);
		//() -> left child, right child 
	}
	return (ret);
}

t_ast_node	*lexar(char *input)
{
	t_ast_node	*head;

	head = init_ast_node(CMD_NODE);
	head->cmd_node->str = input;
	head = recur_lexar(head);	
	return (head);
}
