/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsystem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:39:54 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/19 12:44:42 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSYSTEM_H
# define SUBSYSTEM_H

# include "../main.h"

typedef struct s_cmd_node	t_cmd_node;
/* process_command.c*/


int	process_command(t_cmd_node *cmd_node);

#endif
