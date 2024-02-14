/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:49:02 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/14 12:51:12 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include "../main.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/libft.h"

# define STDIN	0
# define STDOUT	1
# define STDERR	2

# define 

typedef struct s_pipe_io
{
	int	pipe_fd[2];
}	t_pipe_io;

typedef struct s_cmd
{
	int		num_command;
	int		here_doc_flag;
	char	*cmd_dir;
	char	**cmd_argv;
}	t_cmd;

typedef struct s_pipex_args
{
	char	**argv;
	char	**envp;
	int		argc;
}	t_pipex_args;
