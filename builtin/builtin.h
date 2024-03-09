/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:37:09 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 23:40:55 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../main.h"

# define OPTION_FLAG 1
# define PATH_TYPE 2
# define NO_DOT_RELATIVE 4

# define FUNC_SUC	0
# define FUNC_FAIL	1

typedef struct s_minishell	t_minishell;
typedef struct s_ast_node	t_ast_node;
typedef struct s_cmd_node	t_cmd_node;
typedef struct s_str_list	t_str_list;

typedef struct s_cd
{
	int			cd_flag;
	int			directory_index;
	int			i;
	int			start;
	char		*execute_name;
	char		*home_dir;
	char		*cur_path;
	char		*directory;
	char		*cdpath;
	char		**path_arr;
	char		*check_str;
	struct stat	file_stat;
}	t_cd;

/* bulitin.c */
int		process_builtin(t_cmd_node *cmd_node, t_minishell *minishell);

/* ft_echo.c */
void	print_echo(char **str, int nflag);
int		ft_echo(t_cmd_node *cmd_node);
int		ft_isspace(int c);

/* ft_cd_find_curpath.c */
void	find_curpath(t_cd *info, t_minishell *minishell);

/* ft_cd_parse_dot.c */
int		parse_dots(t_cd *info, t_minishell *minishell, t_cmd_node *cmd_node);

/* ft_cd.c */
int		ft_cd(t_cmd_node *cmd_node, t_minishell *minishell);

/* ft_cd2.c */
int		check_cd_option_p(t_cd *info,
			t_cmd_node *cmd_node, t_minishell *minishell);
int		check_directory(t_cd *info,
			t_cmd_node *cmd_node, t_minishell *minishell);

/* ft_cd3 */
void	find_local_dir(t_cd *info, t_minishell *minishell);
void	set_curpath_pwd(t_cd *info, t_minishell *minishell);
void	set_pwd_old_pwd(t_cmd_node *cmd_node,
			t_minishell *minishell, t_cd *info);

/* parse_dot_loop.c */
int		parse_dot_loop(t_cmd_node *cmd_node, t_cd *info,
			t_str_list *stack, t_minishell *minishell);

/* ft_echo.c*/
int		ft_echo(t_cmd_node *cmd_node);

/* ft_env.c */
int		ft_env(t_minishell *minishell);

/* ft_export.c */
int		ft_export(t_cmd_node *cmd_node, t_minishell *minishell);

/* ft_pwd.c */
int		ft_pwd(t_minishell *minishell);

/* ft_unset.c */
int		ft_unset(t_cmd_node *cmd_node, t_minishell *minishell);

/* ft_exit.c */
int		ft_exit(t_cmd_node *cmd_node, t_minishell *minishell);

#endif
