/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:15:18 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/13 13:58:39 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	reset_stdin_out(t_minishell *minishell)
{
	dup2(minishell->stdin_fd, 0);
	dup2(minishell->stdout_fd, 1);
}

int	get_heredoc_fd(t_minishell *minishell, int index)
{
	t_tmp_file	*cur_node;
	int			fd;

	cur_node = minishell->tmp_list->head;
	if (cur_node == NULL)
		return (-1);
	while (--index > 0)
		cur_node = cur_node->next;
	// ft_printf("%s\n", cur_node->tmp);
	fd = open(cur_node->tmp, O_RDONLY);
	return (fd);
}
