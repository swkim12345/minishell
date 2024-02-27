/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:10:28 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/27 14:45:28 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../main.h"

typedef struct s_error
{
	char	*execute_name;
	char	*builtin;
	char	*arg;
	char	*msg;
}	t_error;

/* error_msg.c */
t_error	*set_error_msg(char *execute_name, char *builtin, char *arg, char *msg);
void	free_error(t_error *error);
int		print_error_msg(t_error *error, int error_num, int quote_flag);
int	builtin_error(t_minishell *minishell, char *command, char *arg);


/* error_exit.c */
void	shell_error(t_minishell *minishell, char *command, char *message);
void	extern_cmd_error(t_minishell *minishell, char *command, char *arg);
void	command_not_found_error(t_minishell *minishell, char *command);
void	command_permission_error(t_minishell *minishell, char *command);
void	command_is_directory_error(t_minishell *minishell, char *command);

/* common_util.c */
char	*to_lowercase_str(const char *str);

#endif
