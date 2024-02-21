/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:11:04 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/21 13:31:17 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include "../main.h"

typedef struct s_tree_node	t_tree_node;
typedef struct s_tree_head	t_tree_head;

typedef struct s_tree_node {
	t_tree_node	*left_node;
	t_tree_node	*right_node;
	char		*key;
	char		*value;
	int			index;
}	t_tree_node;

typedef struct s_tree_head {
	t_tree_node	*head;
	long		size;
}	t_tree_head;

/* b_tree_util.c */
int			parse_env(char *env, char **key, char **value);
void		node_delete(t_tree_node *node);
void		recur_tree_delete(t_tree_node *node);
void		exchange_node_key_value(t_tree_node *n, t_tree_node *t);

/* b_tree.c */
int			tree_insert(t_tree_head *head, t_tree_node *leaf);
t_tree_node	*tree_search(t_tree_node *node, t_tree_node **parent, char *key);
t_tree_node	*tree_pop(t_tree_node *head, char *key);
t_tree_head	*char_to_tree(char **str);
int			tree_recurv_traversal(t_tree_node *head, t_tree_node **ordered, int size);
char		**tree_to_char(t_tree_head *head);

/* environ.c */
int			ft_setenv(t_tree_head *head, char *key, char *value);
int			ft_setexport(t_tree_head *head, char *key, char *value);

char		*ft_getenv(t_tree_head *head, char *key); // return value
char		*ft_getexport(t_tree_head *head, char *key);	// return value, if not found, return null

int			ft_unsetexport(t_tree_head *head, char *key);
int			ft_unsetenv(t_tree_head *head, char *key);

t_tree_head	*ft_dup_tree(t_tree_head *head);
t_tree_head	*ft_initenv(t_tree_head *head, char **envp);


#endif
