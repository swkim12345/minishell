/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:00:49 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/08 14:42:28 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXAR_H
# define LEXAR_H

# include "../main.h"

typedef struct s_cmd_node		t_cmd_node;
typedef struct s_ast_node		t_ast_node;
typedef struct s_minishell		t_minishell;
typedef struct s_redirection	t_redirection;
typedef struct s_tmp_file		t_tmp_file;

/* lexar_redirect_helper.c */
int			heredoc_open_fd(t_redirection *red, t_minishell *minishell);
int			find_next_token_red(char *ptr, int index, t_redirection *red);
int			lexar_redirect_err(t_ast_node *node, t_minishell *minishell,
				char *ptr, int index);

/* lexar_err.c */
int			err_token_finder(char *ptr, int index);

/* lexar_redirection.c */
int			lexar_redirect(t_ast_node *node, t_minishell *minishell, int index);

/* lexar_subshell.c */
int			subshell_lexar(t_ast_node *head, int index,
				int flag, t_minishell *minishell);

/* lexar_eof.c */
char		*eof_parser(char *ptr);

/* lexar.c */
int			lexar(t_ast_node *node, t_minishell *minishell);


#endif
