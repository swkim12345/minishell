/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:17:00 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/21 17:18:26 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int			err_msg(char *execute_name, char *builtin, char *arg, char *msg)
{
	printf("%s: %s: `%s': %s\n", execute_name, builtin, arg, msg);
	return (FUNC_FAIL);
}
