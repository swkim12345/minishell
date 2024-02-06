/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:52:51 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/06 20:29:46 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define TRUE		1
# define FALSE		0
# define OR			"||"
# define AND		"&&"
# define BRACKET	"()"
# define DOUBLEQUOT	'\"'
# define SINGLEQUOT	"\'"
# define NO_NODE	0
# define LEFT_NODE	1
# define RIGHT_NODE	2
# define CMD_NODE	4
# include "../libft/libft.h"

typedef struct s_ast_node
{
	t_ast_node			*left_node;
	t_ast_node			*right_node;
	t_list_node			*cmd_node;
	char				*str;
}	t_ast_node;

typedef struct s_list_node
{
	t_list_node *child;
	t_list_node *prev_cmd;
	char *str; 
}	t_list_node;

t_ast_node	*init_ast_node(int child_node);

#endif
