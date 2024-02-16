/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:37:09 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/16 12:46:26 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define OPTION_FLAG 1
# define PATH_TYPE 2
# define NO_DOT_RELATIVE 4

# define FUNC_SUC	0
# define FUNC_FAIL	1

typedef struct	s_cd
{
	int			cd_flag; //0 is default L can be L or P
	int			directory_index;
	char		*home_dir;
	char		*cur_path;
	char		*directory;
	char		*cdpath;
	char		**path_arr;
	char		*check_str;
	struct stat	file_stat;
}	t_cd;

/* ft_echo.c */
void	print_echo(char **str, int nflag);
int     ft_echo(t_cmd_node *cmd_node);
int		ft_isspace(int c);

/* bulitin.c */
int     process_builtin(t_cmd_node *cmd_node);

#endif
