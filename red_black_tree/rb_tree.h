/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:04:35 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/15 20:12:02 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_H
# define RB_TREE_H

# include "../main.h"

# define RED	1
# define BLACK	2

typedef struct s_tree_node	t_tree_node;
typedef struct s_tree_head	t_tree_head;

typedef struct s_tree_head {
	t_tree_node *head;
	int			size;
}	t_tree_head;

typedef struct s_tree_node {
	t_tree_node	*left_node;
	t_tree_node	*right_node;
	t_tree_node	*parent_node;
	int			color;
	char		*key;
	char		*value;
}	t_tree_node;

/* rb_tree.c */
int			rb_tree_insert(t_tree_head *head, t_tree_node *leaf);
t_tree_node	*rb_tree_pop(t_tree_head *head, char *key);

/* rb_tree_util.c */
void		rb_tree_delete(t_tree_head *head);
int			parse_env(char *env, char *key, char *value);

/* rb_tree_tranform.c*/
char		**rb_tree_to_char(t_tree_head *head);
t_tree_head	*char_to_rb_tree(char **str);

#endif
