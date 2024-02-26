/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:11:04 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/26 13:31:54 by sunghwki         ###   ########.fr       */
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

/* binary_tree_mem.c */
t_tree_node	*init_tree_node(void);
void		node_delete(t_tree_node *node);
void		free_tree_delete(t_tree_head *head);

/* binary_tree_util.c */
int			parse_env(char *env, char **key, char **value);
char		*key_value_to_str(t_tree_node *node);
void		exchange_node_key_value(t_tree_node *n, t_tree_node *t);

/* binary_tree.c */
int			tree_insert(t_tree_head *head, t_tree_node *leaf);
t_tree_node	*tree_search(t_tree_node *node, t_tree_node **parent, char *key);
t_tree_node	*tree_pop(t_tree_node *head, char *key);

/* env_to_binary.c */
t_tree_head	*char_to_tree(char **str);
int			tree_recurv_traversal(t_tree_node *head, char **ret_str, int size);
t_tree_head	*ft_push_node_to_tree(t_tree_head *head, char **envp);

/* environ.c */
int			ft_setenv(t_tree_head *head, char *key, char *value);
char		*ft_getenv(t_tree_head *head, char *key); // return value
int			ft_unsetenv(t_tree_head *head, char *key);
t_tree_head	*ft_initenv(char **envp);
char		**ft_charenv(t_tree_head *head);

#endif
