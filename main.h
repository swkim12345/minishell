/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:22:19 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/28 16:51:10 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define EXIT_SUCCESS 0
# define TRUE		1
# define FALSE		0
# define NOTDEFINED	-1

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>

# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"
# include "parser/parser.h"
# include "builtin/builtin.h"
# include "subsystem/subsystem.h"
# include "inner_parser/inner_parser.h"
# include "environ/environ.h"
# include "utils/utils.h"

typedef struct s_minishell	t_minishell;
typedef struct s_str_list	t_str_list;
typedef struct s_tree_node	t_tree_node;
typedef struct s_tree_head	t_tree_head;
typedef struct s_ast_node	t_ast_node;
typedef struct s_cmd_node	t_cmd_node;
typedef struct s_str_node	t_str_node;
typedef struct s_tmp_file	t_tmp_file;
typedef struct s_tmp_list	t_tmp_list;

typedef struct s_tmp_file
{
	char		*tmp;	//임시파일 이름
	int			fd;		//임시파일 디스크립터
	t_tmp_file	*next;
}	t_tmp_file;

typedef struct s_tmp_list
{
	t_tmp_file	*head;
	t_tmp_file	*tail;
}	t_tmp_list;

typedef struct s_minishell
{
	char		*cwd;
	char		*input_str;
	int			exit_code;
  	char		*execute_name;
	char		**envp;
	char		*tmp_file_name;
	int			tmp_file_counter;
	t_tree_head	*env;
	t_tree_head	*export;
	t_tmp_list	*tmp_list;
	t_error		*error;
}	t_minishell;

typedef struct s_cmd_info
{
	char	*cmd;			//명령어
	char	*arguments;		//인자
}	t_cmd_info;

/* main.c */
void	init_shell(t_minishell *shell, char **envp, char **argv);
void	exit_handle(t_minishell *shell, int status);
void	free_t_minishell(t_minishell *shell);

/* common_util.c */
int	str_equal(char *s1, char *s2);
void	set_signal_handler();

#endif
