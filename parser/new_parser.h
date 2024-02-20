/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:45:18 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/20 13:31:47 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_PARSER_H
# define NEW_PARSER_H

# define NOTDEFINED		-1

# define OR				"||"
# define AND			"&&"
# define BRACKET		"()"
# define DOUBLEQUOT		"\""
# define SINGLEQUOT		"\'"
# define PIPE			"|"
# define REDIRINPUT		">"
# define REDIROUTPUT	"<"
//# define SPACE			" "


# define NONODE			0
# define LEFTNODE		1
# define RIGHTNODE		2
# define CMDNODE		4

# include "../main.h"

# define BRACKET_FLAG 1

typedef struct s_cmd_node	t_cmd_node;
typedef struct s_ast_node	t_ast_node;
typedef struct s_minishell	t_minishell;

typedef struct s_cmd_node
{
	int			flag;
	char		*cmd_name;
	char		**str;
	char		**redirect;
}	t_cmd_node;

typedef struct s_ast_node
{
	t_ast_node			*left_node;
	t_ast_node			*right_node;
	t_ast_node			*next_ast_node;
	t_cmd_node			*cmd_node;
	int					flag; //lexar flag
	char				*str;
}	t_ast_node;

#endif
