/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:45:18 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/09 13:32:11 by sunghwki         ###   ########.fr       */
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

# define SYN_ERR		258

# include "../main.h"

typedef struct s_cmd_node		t_cmd_node;
typedef struct s_ast_node		t_ast_node;
typedef struct s_minishell		t_minishell;
typedef struct s_redirection	t_redirection;
typedef struct s_tmp_file		t_tmp_file;

typedef struct s_redirection
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

/* util.c */
void		redirect_node_push(t_ast_node *node, t_redirection *red);
void		tmp_list_push(t_tmp_file *list, t_minishell *minishell);

t_ast_node	*init_ast_node(int child_node);
int			syntax_err_message(char *msg, int end, int ret,
				t_minishell *minishell);
int			finder(char *str, char checker);
int			bracket_finder(char *str);
int			skip_space(char *str);

/* parser_redirect.c */
int			traverse_redirection(t_minishell *minishell);
int			read_heredoc(t_minishell *minishell, t_tmp_file *tmp_file);

/* parser_split.c */
int			split_node(int end, int new_start, t_ast_node *node,
				int new_node_flag);
int			split_recurv_parser(t_ast_node *head, int str_end,
				int dup_str_start, t_minishell *minishell);

/* parser_recurv.c */
int			recurv_parser(t_ast_node *head, t_minishell *minishell);

/* parser.c */
int			read_heredoc(t_minishell *minishell, t_tmp_file *tmp_file);
t_ast_node	*parser(char *str, t_minishell *minishell);
int			recurv_parser(t_ast_node *head, t_minishell *minishell);

/* set_mem.c */
char		**init_doub_char(char **input, int size);
void		free_cmd_node(t_cmd_node **node);
void		free_ast_tree(t_ast_node *head);
void		free_redirection_node(t_redirection *node);

#endif
