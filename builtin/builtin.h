/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:37:09 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/07 15:42:16 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/* ft_echo.c */
void	print_echo(char **str, int nflag);
int     ft_echo(t_cmd_node *cmd_node);
int		ft_isspace(int c);

/* bulitin.c */
int     process_builtin(t_cmd_node *cmd_node);

#endif