/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:28:22 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/13 21:16:55 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_ast_node	*init_ast_node(int child_node)
{
	t_ast_node	*ret;
	t_cmd_node	*node;

	ret = (t_ast_node *)malloc(sizeof(t_ast_node));
	ft_memset((void *)ret, 0, sizeof(ret));
	if (CMDNODE & child_node)
	{
		node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
		ft_memset((void *)node, 0, sizeof(node));
		ret->cmd_node = node;
	}
	if (LEFTNODE & child_node)
		ret->left_node = init_ast_node(CMDNODE);
	if (RIGHTNODE & child_node)
		ret->right_node = init_ast_node(CMDNODE);
	return (ret);
}

static	t_ast_node	*pipe_lexar(t_ast_node *head)
{
	long		index;
	char		*ptr;
	t_ast_node	*ret;
	char		*str;
	
	ptr = head->cmd_node->str[0];
	index = find_pipe(ptr);
	if (ptr[index])
	{
		ret = init_ast_node(CMDNODE);
		ret->next_ast_node = head;
		ptr[index] = '\0';
		str = ft_strdup(ptr);
		ret->cmd_node->str = init_doub_char(&str, 1);
		str = ft_strdup(&str[index + 1]);
		free_doub_char(head->cmd_node->str);
		head->cmd_node->str = init_doub_char(&str, 1);
		recur_lexar(head);
		return (recur_lexar(ret));
	}
	return (head);
}

static	t_ast_node	*or_and_lexar(t_ast_node *head)
{
	char		*ptr;
	long		index;
	char		*str;
	t_ast_node	*ret;

	ptr = head->cmd_node->str[0];
	index = find_or_and_bracket(ptr);
	if (!str_cmp(&ptr[index], OR) || !str_cmp(&ptr[index], AND))
	{
		ret = init_ast_node(RIGHTNODE);
		ret->next_ast_node = head->next_ast_node;
		if (!str_cmp(&ptr[index], OR))
			str = ft_strdup(OR);
		else
			str = ft_strdup(AND);
		ret->str = str;
		ptr[index] = '\0';
		str = ft_strdup(&ptr[index + 2]);
		ret->right_node->cmd_node->str = init_doub_char(&str, 1);
		str = ft_strdup(ptr);
		free_doub_char(head->cmd_node->str);
		head->cmd_node->str = init_doub_char(&str, 1);
		ret->left_node = head;
		recur_lexar(ret->left_node);
		recur_lexar(ret->right_node);
		return (ret);
	}
	return (head);
}

t_ast_node	*recur_lexar(t_ast_node *head)
{
	t_ast_node	*ret;
	char		*ptr;
	long		index;

	ptr = head->cmd_node->str[0];
	ret = pipe_lexar(head);
	if (ret != head)
		return (ret);
	ret = or_and_lexar(head);
	if (ret != head)
		return (ret);
	return (ret);
}

t_ast_node	*lexar(char *input)
{
	t_ast_node	*head;
	char		*i;

	head = init_ast_node(CMDNODE);
	i = ft_strdup(input);
	head->cmd_node->str = init_doub_char(&i, 1);
	head = recur_lexar(head);	
	return (head);
}
