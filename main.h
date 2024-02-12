/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:22:19 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/12 23:38:00 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define EXIT_SUCCESS 0
# define TRUE		1
# define FALSE		0
# define NOTDEFINED	-1
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "parser/parser.h"
# include "builtin/builtin.h"
# include "inner_parser/inner_parser.h"

typedef struct s_minishell
{
    char    *cwd;
    char    *input_str;
    
}   t_minishell;

typedef struct s_cmd_info
{
	char	*cmd;
	char	*arguments;
}	t_cmd_info;

/* common_util.c */
int	str_equal(char *s1, char *s2);

#endif
