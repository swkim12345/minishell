/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:52:51 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/06 13:09:54 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_ast_node
{
	t_ast_node			*left_node;
	t_ast_node			*right_node;
	t_list_node			*cmd_node;
	char				*str;
}	t_ast_node;

typedef struct s_list_node
{
	struct s_list_node *child; //opt, str
	char *str; //cmd
}	t_list_node;

#endif
