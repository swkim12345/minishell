/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:22:19 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/20 17:30:26 by sunghwki         ###   ########.fr       */
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

typedef struct s_minishell	t_minishell;
typedef struct s_str_list	t_str_list;
typedef struct s_tree_node	t_tree_node;
typedef struct s_tree_head	t_tree_head;
typedef struct s_ast_node	t_ast_node;
typedef struct s_cmd_node	t_cmd_node;
typedef struct s_str_node	t_str_node;
typedef struct s_str_list	t_str_list;
typedef struct s_minishell	t_minishell;

typedef struct tmp_file
{
	char	*tmp;	//임시파일 이름
	int		fd;		//임시파일 디스크립터
}	t_tmp_file;

typedef struct s_minishell
{
	char		**envp;		//환경변수
	char		*cwd;		//현재 디렉토리
	char		*execute_name;	//실행파일 이름
	char		*input_str;	//입력받은 문자열
	int			exit_code;		//종료코드
	int			here_doc_counter;	//here_doc 카운터
	t_tmp_file	*here_doc;	//here_doc 파일
	t_tree_head	*env;	//환경변수 트리
}	t_minishell;

typedef struct s_cmd_info
{
	char	*cmd;			//명령어
	char	*arguments;		//인자
}	t_cmd_info;

/* common_util.c */
int	str_equal(char *s1, char *s2);

#endif
