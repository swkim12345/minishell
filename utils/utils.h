/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:10:28 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 23:38:03 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../main.h"

typedef struct s_tmp_file		t_tmp_file;
typedef struct s_tmp_list		t_tmp_list;
typedef struct s_redirection	t_redirection;

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
int		builtin_error(t_minishell *minishell, char *command, char *arg);

/* cd_error_msg.c */
int		cd_error(t_cd *info, t_minishell *minishell, char *command, char *arg);
int		home_not_set_error(t_minishell *minishell, char *command, char *arg);
int		not_a_directory_error(t_cd *info, t_minishell *minishell,
			char *command, char *arg);

/* error_exit.c */
void	shell_error(t_minishell *minishell, char *command, char *message);
void	extern_cmd_error(t_minishell *minishell, char *command, char *arg);
void	command_not_found_error(t_minishell *minishell, char *command);
void	command_permission_error(t_minishell *minishell, char *command);
void	command_is_directory_error(t_minishell *minishell, char *command);

/* error_exit2.c */
void	command_no_such_file(t_minishell *minishell, char *command);

/* common_util.c */
int		str_equal(char *s1, char *s2);
int		ft_isspace(int c);
char	*to_lowercase_str(const char *str);
void	free_2d_str(char **arr);

/* tmp_list.c */
void	free_tmp_list(t_tmp_list *list, t_minishell *minishell,
			int unlink_flag);
void	clear_tmp_list(t_tmp_list *list, t_minishell *minishell,
			int unlink_flag);

/* error_redirection.c */
int		redirection_error(t_minishell *minishell,
			t_redirection *redirect_node);
int		ambiguous_redirect_error(t_minishell *minishell,
			t_redirection *redirect_node, char **file_list);

#endif
