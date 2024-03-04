/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:14:59 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/04 21:30:25 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	shell_error(t_minishell *minishell, char *command, char *arg)
{
	int	status;

	status = errno;
	//printf("shell_error\n");
	minishell->error
		= set_error_msg(minishell->execute_name, command, arg, 0);
	print_error_msg(minishell->error, 0, 0);
	exit(status);
}

void	extern_cmd_error(t_minishell *minishell, char *command, char *arg)
{
	int	status;

	status = errno;
	minishell->error
		= set_error_msg(minishell->execute_name, command, arg, 0);
	print_error_msg(minishell->error, 0, 0);
	exit(status);
}

void	command_not_found_error(t_minishell *minishell, char *command)
{
	minishell->error = set_error_msg(minishell->execute_name,
			command, 0, "command not found");
	print_error_msg(minishell->error, 127, 0);
	exit(127);
}

void	command_permission_error(t_minishell *minishell, char *command)
{
	minishell->error = set_error_msg(minishell->execute_name,
			command, 0, "Permission denied");
	print_error_msg(minishell->error, 126, 0);
	exit(126);
}

void	command_is_directory_error(t_minishell *minishell, char *command)
{
	minishell->error = set_error_msg(minishell->execute_name,
			command, 0, "is a directory");
	print_error_msg(minishell->error, 126, 0);
	exit(126);
}
