/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:03:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/21 13:14:36 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	main(int argc, char **argv, char **envp)
{
	t_tree_head	*head;
	t_tree_node	*tmp;
	char		**ret;
	char		*key;
	char		*value;
	int			index;

	index = -1;
	while (envp[++index])
	{
		printf("%d : %s\n", index, envp[index]);
	}
	head = char_to_tree(envp);
	printf("head size : %ld\n", head->size);
	index = -1;
	while (envp[++index])
	{
		parse_env(envp[index], &key, &value);
		printf("key : %s, node value : %s, real value: %s\n",key, tree_search(head->head, &tmp, key)->value, value);
	}
	printf("key : %s, node value : %s, real value: %s\n", "_", tree_search(head->head, &tmp, "_")->value, "velu");
	ret = tree_to_char(head);
	index = -1;
	while (ret[++index])
	{
		printf("%d : %s\n", index, ret[index]);
	}
	return (0);
}

ft_
