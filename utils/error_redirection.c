/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:17:33 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 23:37:52 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	redirection_error(t_minishell *minishell,
		t_redirection *redirect_node)
{
	minishell->error
		= set_error_msg(minishell->execute_name, redirect_node->str, 0, 0);
	print_error_msg(minishell->error, 0, 0);
	return (1);
}

int	ambiguous_redirect_error(t_minishell *minishell,
		t_redirection *redirect_node, char **file_list)
{
	minishell->error
		= set_error_msg(minishell->execute_name, redirect_node->str, 0, 0);
	print_error_msg(minishell->error, 1, 0);
	free_2d_str(file_list);
	return (1);
}
