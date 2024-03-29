/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:33:29 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/13 16:59:21 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	syntax_err_message(char *msg, int end, int ret, t_minishell *minishell)
{
	if (end != NOTDEFINED && end != -2 && ft_strlen(msg) >= (size_t)end)
		msg[end] = '\0';
	ft_putstr_fd(minishell->execute_name, STDERR_FILENO);
	ft_putstr_fd(": syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	minishell->exit_code = ret;
	return (ret);
}

void	redirect_node_push(t_ast_node *node, t_redirection *red)
{
	t_redirection	*tmp;

	if (node->red == NULL)
		node->red = red;
	else
	{
		tmp = node->red;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = red;
	}
}

int	finder(char *str, char checker)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (str[index] == checker)
			return (index);
	}
	return (NOTDEFINED);
}

int	bracket_finder(char *str)
{
	int	count;
	int	index;

	index = 0;
	if (*str == '(')
	{
		count = 1;
		while (str[++index])
		{
			if (str[index] == '(')
				count++;
			if (str[index] == ')')
				count--;
			if (count == 0)
				return (index);
		}
	}
	return (NOTDEFINED);
}

int	skip_space(char *str)
{
	int	index;

	index = 0;
	if (str[index] == '\0')
		return (index);
	while (str[index] == ' ' || (str[index] >= 9 && str[index] <= 13))
		index++;
	return (index);
}
