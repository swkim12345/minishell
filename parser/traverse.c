/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:25:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/14 19:20:42 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	recur_traverse(t_ast_node *head) //fork로 실행, wait를 통해 wait, 이후 pipe관련 처리
{
	int	ret;

	if (!head)
		return (TRUE); //fix 필요(true만 리턴하면 안됨.)
	ret = traverse(head->left_node);
	if (head->cmd_node)
	{
		printf("cmd_node : %s\n", head->cmd_node->str[0]);
		printf("cmd redirection : %s\n", head->cmd_node->redirect);
		return (TRUE);
	}
	if (head->str)
		printf("str : %s\n", head->str);
	if ((!str_cmp(head->str, AND) && ret) ||
	(!str_cmp(head->str, OR) && !ret))
		ret = traverse(head->right_node);
	return (ret);
}

int	traverse(t_ast_node *head)
{
	int	ret;
	
	if (!head)
		return (TRUE);
	if (head)
		ret = recur_traverse(head);
	if (head->next_ast_node)
	{
		printf("find next pipe\n");
		ret = recur_traverse(head->next_ast_node);
	}
	return (ret);
}
