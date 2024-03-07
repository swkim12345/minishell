/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsystem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:39:54 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 16:48:48 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSYSTEM_H
# define SUBSYSTEM_H

# include "../main.h"

typedef struct s_cmd_node	t_cmd_node;
/* process_command.c*/
int		process_command(t_cmd_node *cmd_node, t_minishell *minishell);

/* process_extern_command.c */
int		process_extern_cmd(t_cmd_node *cmd_node, t_minishell *minishell);
char	*find_from_path(t_cmd_node *cmd_node, t_minishell *minishell);
int		check_file_valid(char *execute_path, t_cmd_node *cmd_node,
			t_minishell *minishell);

/* process_extern_command2.c */
void	process_extern_cmd_no_slash(t_cmd_node *cmd_node,
			t_minishell *minishell);

#endif
