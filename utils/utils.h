/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:10:28 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/22 18:06:15 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../main.h"

typedef struct s_error
{
	char	*execute_name;
	char	*builtin;
	char	*arg;
	char	*msg;
}	t_error;

/* error_msg.c */
int		print_error_msg(t_error *error, int error_num, int quote_flag);
t_error	*set_error_msg(char *execute_name, char *builtin, char *arg, char *msg);
void	free_error(t_error *error);

/*  */

#endif
