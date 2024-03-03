/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:45:18 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/03 11:57:49 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define NOTDEFINED		-1

# define OR				"||"
# define AND			"&&"
# define BRACKET		"()"
# define DOUBLEQUOT		"\""
# define SINGLEQUOT		"\'"
# define PIPE			"|"
# define REDIRINPUT		">"
# define REDIROUTPUT	"<"

# define BRACKET_FLAG 1
# define STRING_FLAG 2

# define LT_SIGN 1
# define DB_LT_SIGN 2
# define GT_SIGN 4
# define DB_GT_SIGN 8

# define NO_FLAG 0
# define OR_FLAG 1
# define AND_FLAG 2

# define NONODE			0
# define LEFTNODE		1
# define RIGHTNODE		2
# define NEXTNODE		4
# define CMDNODE		8

# include "../main.h"


typedef struct s_cmd_node		t_cmd_node;
typedef struct s_ast_node		t_ast_node;
typedef struct s_minishell		t_minishell;
typedef struct s_redirection	t_redirection;
typedef struct s_tmp_file		t_tmp_file;

typedef struct s_redirection 
{
	int							index;	//if heredoc:index or not use NOTDEFINED
	int							flag;	// 0: <, 1: <<, 2: >, 4: >>
	char						*str;	// file name or here doc delim
	t_redirection				*next;
}	t_redirection;

typedef struct s_cmd_node
{
	char						*cmd_name;	//command name
	char						**str;		//command arguments
}	t_cmd_node;

typedef struct s_ast_node
{
	t_ast_node					*left_node;
	t_ast_node					*right_node;
	t_ast_node					*next_ast_node;	//for pipe
	t_cmd_node					*cmd_node;		
	t_redirection				*red;	//redirection array
	int							flag;	//subshell flag
	int							index;	//redirection index in t_minishell
	int							err_flag;	//syntax error flag, TRUE -> stop parsing
}	t_ast_node;

typedef struct s_pipe_io
{
	int	pipe_fd[2];
}	t_pipe_io;

typedef struct s_pipe_traverse
{
	int			ret;
	int			num_pipe;
	int			current_pipe;
	pid_t		pid;
	pid_t		first_pid;
	t_pipe_io	*pipe_list;
}	t_pipe_traverse;


/* util.c */
void		redirect_node_push(t_ast_node *node, t_redirection *red);
void		tmp_list_push(t_tmp_file *list, t_minishell *minishell);

t_ast_node	*init_ast_node(int child_node);
int			syntax_err_message(char *msg, int end, int ret,
				t_minishell *minishell);
int			finder(char *str, char checker);
int			bracket_finder(char *str);
int			skip_space(char *str);

/* set_mem.c */
char		**init_doub_char(char **input, int size);
void		free_cmd_node(t_cmd_node **node);
void		free_ast_tree(t_ast_node *head);
void		free_redirection_node(t_redirection *node);

/* lexar.c */
int			lexar(t_ast_node *node, t_minishell *minishell);

/* parser.c */
int	read_heredoc(t_minishell *minishell, t_redirection *redirection
	, t_tmp_file *tmp_file);
t_ast_node	*parser(char *str, t_minishell *minishell);
int			recurv_parser(t_ast_node *head, t_minishell *minishell);
int			traverse(t_ast_node *head, t_minishell *minishell, int check_pipe);

/* traverse.c */
int	recur_traverse(t_ast_node *head, t_minishell *minishell); //fork로 실행, wait를 통해 wait, 이후 pipe관련 처리
int	subshell_traverse(t_ast_node *head, t_minishell *minishell);
int	get_num_pipe(t_ast_node *head);
int	wait_processes(pid_t last_pid, pid_t first_pid);
t_pipe_io	*init_pipe_list(int num_pipe);
void	set_pipe_redirection(t_pipe_traverse *info, t_minishell *minishell);
int	pipe_traverse(t_ast_node *head, t_minishell *minishell);
int	set_read_fd(t_ast_node *ast_node, t_minishell *minishell);
int set_write_fd(t_ast_node *ast_node, t_minishell *minishell);
int	process_redirection(t_ast_node *ast_node, t_minishell *minishell);
int	traverse(t_ast_node *head, t_minishell *minishell, int check_pipe);



#endif
