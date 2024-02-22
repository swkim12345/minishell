/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:14:59 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/22 16:59:15 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	shell_error(t_minishell *minishell, char *command, char *message)
{
	int	status;

	status = errno;
	ft_putstr_fd(minishell->execute_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(message);
	exit(status);
}

void	

void	command_not_found_error(t_minishell *minishell, char *command)
{
	ft_putstr_fd(minishell->execute_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127);
}

void	command_permission_error(t_minishell *minishell, char *message)
{
	ft_putstr_fd(minishell->execute_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	// write(2, message, ft_strlen(message));
	// write(2, ": ", 2);
	perror(message);
	exit(126);
}

void	command_is_directory_error(t_minishell *minishell, char *message)
{
	ft_putstr_fd(minishell->execute_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd(": is a direction\n", STDERR_FILENO);
	exit(126);
}