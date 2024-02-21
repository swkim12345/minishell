/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsystem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:39:54 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/21 15:17:10 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSYSTEM_H
# define SUBSYSTEM_H

# include "../main.h"

# define SLASH 1

typedef struct s_cmd_node	t_cmd_node;
/* process_command.c*/

int	process_command(t_cmd_node *cmd_node, t_minishell *minishell);

#endif
