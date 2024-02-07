/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:20:26 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/07 13:52:53 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

/*
	cmd struct list
*/

int	is_builtin_fn(t_cmd_node *cmd_node)
{
	char	*str;

	str = cmd_node->cmd_name;
	if (str_equal)
}

int	process_command(t_cmd_node *cmd_node)
{
	cmd_node->cmd_name = cmd_node->str[0];
	if (is_builtin_fn(cmd_node))
		process_builtin(cmd_node);
}