/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:52:51 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/13 22:45:40 by sunghwki         ###   ########.fr       */
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

# define NONODE			0
# define LEFTNODE		1
# define RIGHTNODE		2
# define CMDNODE		4

typedef struct s_ast_node	t_ast_node;
typedef struct s_cmd_node	t_cmd_node;

typedef struct s_ast_node
{
	t_ast_node			*left_node;
	t_ast_node			*right_node;
	t_ast_node			*next_ast_node;
	t_cmd_node			*cmd_node;
	char				*str;
}	t_ast_node;

typedef struct s_cmd_node
{
	char		*cmd_name;
	char		**str;
	char		*redir;
}	t_cmd_node;

t_ast_node	*init_ast_node(int child_node);
/* finder.c */
/* find_or_and_bracket / find_bracket : exclusive quot */
long		find_end_quote(char *input);
long		find_or_and(char *input);
long		find_bracket(char *input);
long		find_pipe(char *input);

/* set_mem.c */
char		**init_doub_char(char **input, int size);
void		free_cmd_node(t_cmd_node *node);
void		free_doub_char(char **input);

/* lexar.c */
t_ast_node	*lexar(char *input);
t_ast_node	*recur_lexar(t_ast_node *head);

/* util.c */
int	str_cmp(char *str_org, char *str_cmp);

/* traverse.c */
int			traverse(t_ast_node *head);

#endif
