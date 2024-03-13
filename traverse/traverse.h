/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:33:19 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/13 16:06:25 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAVERSE_H
# define TRAVERSE_H

# include "../main.h"

typedef struct s_pipe_io
{
	int	pipe_fd[2];
}	t_pipe_io;

typedef struct s_pipe_traverse
{
	int			ret;
	int			num_pipe;
	int			current_pipe;
	pid_t		pid;
	pid_t		first_pid;
	t_pipe_io	*pipe_list;
}	t_pipe_traverse;

/* traverse.c */
int			recur_traverse(t_ast_node *head,
				t_minishell *minishell, int recur_mode);
int			subshell_traverse(t_ast_node *head, t_minishell *minishell);
int			get_num_pipe(t_ast_node *head);
int			pipe_traverse(t_ast_node *head, t_minishell *minishell);
int			set_read_fd(t_redirection *redirect_node, t_minishell *minishell,
				t_ast_node *ast_node);
int			set_write_fd(t_redirection *redirect_node, t_minishell *minishell);
int			process_redirection(t_ast_node *ast_node, t_minishell *minishell);
int			traverse(t_ast_node *head, t_minishell *minishell,
				int check_pipe, int recur_mode);

/* pipe_traverse.c */
int			wait_processes(pid_t last_pid, pid_t first_pid);
t_pipe_io	*init_pipe_list(int num_pipe);
void		set_pipe_redirection(t_pipe_traverse *info, t_minishell *minishell);
void		process_pipe_child(t_minishell *minishell, t_pipe_traverse *info,
				t_ast_node *head);
int			get_num_pipe(t_ast_node *head);

/* redirection.c */
int			set_read_fd(t_redirection *redirect_node, t_minishell *minishell,
				t_ast_node *ast_node);
int			set_write_fd(t_redirection *redirect_node, t_minishell *minishell);
int			process_redirection(t_ast_node *ast_node, t_minishell *minishell);

/* redirection_util.c */
void		reset_stdin_out(t_minishell *minishell);
int			get_heredoc_fd(t_minishell *minishell, int index);

/* traverse_util.c */
void		init_pipe_traverse(t_ast_node *head,
				t_pipe_traverse *info, t_minishell *minishell);

#endif
