/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:17:00 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/22 17:56:14 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	print_error_msg_arg(char *arg, int quote_flag)
{
	if (quote_flag)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("\'", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
}

int	print_error_msg(t_error *error, int error_num, int quote_flag)
{
	if (error->execute_name)
	{
		ft_putstr_fd(error->execute_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error->builtin)
	{
		ft_putstr_fd(error->builtin, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error->arg)
		print_error_msg_arg(error->arg, quote_flag);
	if (error_num == 0)
		perror(0);
	else
		ft_putstr_fd(error->msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (FUNC_FAIL);
}
