/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:22:19 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/04 12:18:18 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define EXIT_SUCCESS	0
# define TRUE			1
# define FALSE			0
# define NOTDEFINED		-1

# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define BLUE			"\033[0;34m"
# define MAGENTA		"\033[0;35m"
# define CYAN			"\033[0;36m"
# define WHITE			"\033[0;37m"

# define BOLD			"\033[1m"
# define BOLD_RED		"\033[1;31m"
# define BOLD_GREEN		"\033[1;32m"
# define BOLD_YELLOW	"\033[1;33m"
# define BOLD_BLUE		"\033[1;34m"
# define BOLD_MAGENTA	"\033[1;35m"
# define BOLD_CYAN		"\033[1;36m"
# define BOLD_WHITE		"\033[1;37m"
# define RESET			"\033[0m"

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

# include "libft///ft_printf.h"
# include "parser/parser.h"
# include "builtin/builtin.h"
# include "subsystem/subsystem.h"
# include "inner_parser/inner_parser.h"
# include "environ/environ.h"
# include "utils/utils.h"
# include "signal/signal.h"

# define NOT_CHECK_RED 1

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
	char		*eof;	//heredoc 종료문자열
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
	char		*print_str;
	char		**envp;
	char		*tmp_file_name;
	int			tmp_file_counter;
	int			stdin_fd;
	int			stdout_fd;
	int			flag;
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

/* traverse.c */
t_tmp_file	*get_heredoc_file(t_minishell *minishell, int index);

#endif
