/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:17:00 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/21 19:34:35 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int			err_msg(char *execute_name, char *builtin, char *arg, char *msg, int arg_quote)
{
	if (!arg)
		printf("%s: %s: %s\n", execute_name, builtin, msg);
	else if (arg_quote)
		printf("%s: %s: `%s': %s\n", execute_name, builtin, arg, msg);
	else
		printf("%s: %s: %s: %s\n", execute_name, builtin, arg, msg);
	return (FUNC_FAIL);
}

int			err_msg_exit(char *execute_name, char *builtin, char *arg, char *msg, int arg_quote)
{
	err_msg(execute_name, builtin, arg, msg, arg_quote);
	exit (FUNC_FAIL);
}
