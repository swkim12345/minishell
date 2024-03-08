/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:45:18 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/08 13:00:22 by sunghwki         ###   ########.fr       */
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

# define BRACKET_FLAG 16
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

typedef struct	s_redirection
{
	int							index;
	int							flag;
	char						*str;
	t_redirection				*next;
}	t_redirection;

typedef struct s_cmd_node
{
	char						*cmd_name;
	char						**str;
}	t_cmd_node;

typedef struct s_ast_node
{
	t_ast_node					*left_node;
	t_ast_node					*right_node;
	t_ast_node					*next_ast_node;
	t_cmd_node					*cmd_node;		
	t_redirection				*red;
	int							flag;
	int							index;
	int							err_flag;
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

/* lexar_redirect_helper.c */
int			heredoc_open_fd(t_redirection *red, t_minishell *minishell);
int			find_next_token_red(char *ptr, int index, t_redirection *red);
int			lexar_redirect_err(t_ast_node *node, t_minishell *minishell,
				char *ptr, int index);

/* parser_redirect.c */
int			traverse_redirection(t_minishell *minishell);
int			read_heredoc(t_minishell *minishell, t_tmp_file *tmp_file);

/* parser_split.c */
int			split_node(int end, int new_start, t_ast_node *node, int new_node_flag);
int			split_recurv_parser(t_ast_node *head, int str_end,
					int dup_str_start, t_minishell *minishell);

/* parser_recurv.c */
int			recurv_parser(t_ast_node *head, t_minishell *minishell);

/* parser.c */
t_ast_node	*parser(char *str, t_minishell *minishell);


/* set_mem.c */
char		**init_doub_char(char **input, int size);
void		free_cmd_node(t_cmd_node **node);
void		free_ast_tree(t_ast_node *head);
void		free_redirection_node(t_redirection *node);

/* lexar_err.c */
int			err_token_finder(char *ptr, int index);

/* lexar_redirection.c */
int			lexar_redirect(t_ast_node *node, t_minishell *minishell, int index);

/* lexar_subshell.c */
int			subshell_lexar(t_ast_node *head, int index,
				int flag, t_minishell *minishell);

/* lexar.c */
char		*eof_parser(char *ptr);
int			lexar(t_ast_node *node, t_minishell *minishell);

/* parser.c */
int			read_heredoc(t_minishell *minishell, t_tmp_file *tmp_file);
t_ast_node	*parser(char *str, t_minishell *minishell);
int			recurv_parser(t_ast_node *head, t_minishell *minishell);
int			traverse(t_ast_node *head, t_minishell *minishell, int check_pipe);

/* traverse.c */
int			recur_traverse(t_ast_node *head, t_minishell *minishell);
int			subshell_traverse(t_ast_node *head, t_minishell *minishell);
int			get_num_pipe(t_ast_node *head);
int			pipe_traverse(t_ast_node *head, t_minishell *minishell);
int			set_read_fd(t_redirection *redirect_node, t_minishell *minishell,
				t_ast_node *ast_node);
int			set_write_fd(t_redirection *redirect_node, t_minishell *minishell);
int			process_redirection(t_ast_node *ast_node, t_minishell *minishell);
int			traverse(t_ast_node *head, t_minishell *minishell, int check_pipe);

/* pipe_traverse.c */
int			wait_processes(pid_t last_pid, pid_t first_pid);
t_pipe_io	*init_pipe_list(int num_pipe);
void		set_pipe_redirection(t_pipe_traverse *info, t_minishell *minishell);
void		process_pipe_child(t_minishell *minishell, t_pipe_traverse *info,
				t_ast_node *head);
int			get_num_pipe(t_ast_node *head);

/* redirection.c */
int			set_read_fd(t_redirection *redirect_node, t_minishell *minishell,
				t_ast_node *ast_node);
int			set_write_fd(t_redirection *redirect_node, t_minishell *minishell);
int			process_redirection(t_ast_node *ast_node, t_minishell *minishell);

/* redirection_util.c */
void		reset_stdin_out(t_minishell *minishell);
int			get_heredoc_fd(t_minishell *minishell, int index);

#endif
