/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:56:56 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 16:57:06 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	cd_error(t_cd *info, t_minishell *minishell, char *command, char *arg)
{
	free(info->cur_path);
	return (builtin_error(minishell, command, arg));
}

int	home_not_set_error(t_minishell *minishell, char *command, char *arg)
{
	minishell->error = set_error_msg(minishell->execute_name, command,
			arg, "HOME not set");
	print_error_msg(minishell->error, 1, 0);
	return (1);
}

int	builtin_error(t_minishell *minishell, char *command, char *arg)
{
	minishell->error = set_error_msg(minishell->execute_name, command, arg, 0);
	print_error_msg(minishell->error, 0, 0);
	return (1);
}
