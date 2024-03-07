/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:50:06 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 16:55:09 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	clear_tmp_list(t_tmp_list *list, t_minishell *minishell,
		int unlink_flag)
{
	t_tmp_file	*cur;
	t_tmp_file	*next;

	if (!list)
		return ;
	cur = list->head;
	list->head = NULL;
	list->tail = NULL;
	while (cur)
	{
		next = cur->next;
		if (unlink_flag)
			unlink(cur->tmp);
		free(cur->tmp);
		free(cur->eof);
		free(cur);
		cur = next;
	}
	minishell->tmp_file_counter = 0;
}

void	free_tmp_list(t_tmp_list *list, t_minishell *minishell, int unlink_flag)
{
	clear_tmp_list(list, minishell, unlink_flag);
	free(list);
	list = 0;
}

void	tmp_list_push(t_tmp_file *file, t_minishell *minishell)
{
	if (minishell->tmp_list == NULL)
	{
		minishell->tmp_list = (t_tmp_list *)ft_calloc(sizeof(t_tmp_list), 1);
	}
	if (minishell->tmp_list->tail == NULL)
	{
		minishell->tmp_list->head = file;
		minishell->tmp_list->tail = file;
	}
	else
	{
		minishell->tmp_list->tail->next = file;
		minishell->tmp_list->tail = file;
	}
	minishell->tmp_file_counter++;
}
