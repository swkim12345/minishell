/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:58:49 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/13 16:05:46 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	init_pipe_traverse(t_ast_node *head,
		t_pipe_traverse *info, t_minishell *minishell)
{
	info->current_pipe = -1;
	info->num_pipe = get_num_pipe(head);
	info->pipe_list = init_pipe_list(info->num_pipe);
	dup2(minishell->stdin_fd, 0);
	dup2(minishell->stdout_fd, 1);
}
