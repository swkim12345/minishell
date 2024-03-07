/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:55:54 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 16:56:08 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	command_no_such_file(t_minishell *minishell, char *command)
{
	minishell->error = set_error_msg(minishell->execute_name,
			command, 0, "No such file or directory");
	print_error_msg(minishell->error, 126, 0);
	exit(127);
}
