/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:52:51 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/07 21:41:58 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H


# define NOTDEFINED	-1
# define OR			"||"
# define AND		"&&"
# define BRACKET	"()"
# define DOUBLEQUOT	"\""
# define SINGLEQUOT	"\'"
# define NO_NODE	0
# define LEFT_NODE	1
# define RIGHT_NODE	2
# define CMD_NODE	4

typedef struct s_ast_node	t_ast_node;
typedef struct s_cmd_node	t_cmd_node;

typedef struct s_ast_node
{
	t_ast_node			*left_node;
	t_ast_node			*right_node;
	t_cmd_node			*cmd_node;
	char				*str;
}	t_ast_node;

typedef struct s_cmd_node
{
	t_cmd_node	*next_cmd;
	char		*cmd_name;
	char		**str;
}	t_cmd_node;

t_ast_node	*init_ast_node(int child_node);
/* finder.c */
/* find_or_and_bracket / find_bracket : exclusive quot */
long		find_or_and_bracket(char *input);
long		find_bracket(char *input);
long		find_quot(char *input, int is_double);

/* util.c */
char		**init_doub_char(char **input, int size);
void		free_cmd_node(t_cmd_node *node);
void		free_doub_char(char **input);

/* lexar.c */
t_ast_node	*lexar(char *input);
#endif
