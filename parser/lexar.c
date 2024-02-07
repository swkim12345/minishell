/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:28:22 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/07 13:34:41 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../main.h"

t_ast_node	*init_ast_node(int child_node)
{
	t_ast_node	*ret;
	t_cmd_node	*node;
	
	ret = (t_ast_node *)malloc(sizeof(t_ast_node));
	ft_memset((void *)ret, 0, sizeof(ret));
	if (CMD_NODE & child_node)
	{
		node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
		ft_memset((void *)node, 0, sizeof(node));
		ret->cmd_node = node;
	}
	if (LEFT_NODE & child_node)
		ret->left_node = init_ast_node(CMD_NODE);
	if (RIGHT_NODE & child_node)
		ret->right_node = init_ast_node(CMD_NODE);
	return (ret);
}
 
t_ast_node	*recur_lexar(t_ast_node *head)
{
	t_ast_node	*ret;
	char		*ptr;
	char		*str;
	long		index;
	long		tmp;
	long		bracket_count;
	
	ptr = head->cmd_node->str;
	index = 0;
	//|| && check -> no -> return head
	if (!find_or_and_bracket(ptr))
		return (head);
	while (ptr[index])
	{
		index = find_or_and_bracket(ptr);
		//first meet : () => delete!
		if (!ft_strncmp(ptr, &BRACKET[0], 1))
		{
			bracket_count = 1;
			tmp = index;
			ft_strlcpy(&ptr[index], &ptr[index + 1], ft_strlen(&ptr[index + 1]));
			while (ptr[tmp])
			{
				tmp = find_bracket(&ptr[index]);
				if (ptr[tmp] == BRACKET[0])
					bracket_count++;
				else
					bracket_count--;
				if (!bracket_count)
					break;
				tmp++;
			}
			ft_strlcpy(&ptr[tmp], &ptr[tmp + 1], ft_strlen(&ptr[tmp + 1]));
		}
		//|| && -> left(left_childe cmd_node), right(right_child, cmd_node), head->cmd_node(|| or &&)
		//각각 recurve
		if (!ft_strncmp(&ptr[index], OR, 2) || !ft_strncmp(&ptr[index], AND, 2))
		{
			ret = init_ast_node(RIGHT_NODE);
			if (!ft_strncmp(&ptr[index], OR, 2))
			{
				str = ft_strdup(OR);
				ret->str = str;
			}
			else
			{
				str = ft_strdup(AND);
				ret->str = str;
			}
			ptr[index] = '\0';
			str = ft_strdup(&head->cmd_node->str[index + 2]);
			ret->right_node->cmd_node->str = str;
			str = ft_strdup(head->cmd_node->str);
			head->cmd_node->str = str;
			ret->left_node = head;
			free(ret->cmd_node->str);
			free(ret->cmd_node);
			recur_lexar(ret->left_node);
			recur_lexar(ret->right_node);
			return (ret);
		}
		index++;
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
