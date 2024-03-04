/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsystem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:39:54 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/04 17:34:47 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSYSTEM_H
# define SUBSYSTEM_H

# include "../main.h"

# define SLASH 1

typedef struct s_cmd_node	t_cmd_node;
/* process_command.c*/
int	is_builtin_fn(t_cmd_node *cmd_node);
int	process_command(t_cmd_node *cmd_node, t_minishell *minishell);
int	process_extern_cmd(t_cmd_node *cmd_node, t_minishell *minishell);
void	print_ast_node(t_ast_node *ast_node);
void	print_cmd_node(t_cmd_node *cmd_node);

#endif
