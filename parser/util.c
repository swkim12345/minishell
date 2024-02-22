/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:33:29 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/22 14:21:48 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	syntax_err_message(char *msg, int end, int ret, t_minishell *minishell)
{
	msg[end] = '\0';
	ft_putstr_fd(minishell->execute_name, STDERR_FILENO);
	ft_putstr_fd(": syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (ret);
}

void	free_ast_tree(t_ast_node *head)
{
	t_redirection	*tmp;
	int				i;

	free_ast_tree(head->left_node && head->right_node && head->next_ast_node);
	if (head->cmd_node)
	{
		if (head->cmd_node->cmd_name)
			free(head->cmd_node->cmd_name);
		if (head->cmd_node->str)
			free_doub_char(head->cmd_node->str);
		free(head->cmd_node);
	}
	if (head->red)
	{
		i = 0;
		tmp = head->red;
		while (tmp[i].str)
		{
			free(tmp[i].str);
			i++;
		}
		free(tmp);
	}
	free(head);
}

char	*dup_str(char *str, int start, int end)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (end - start + 1));
	ret[end - start] = '\0';
	ft_memmove((void *)ret, (void *)&str[start], end - start);
	return (ret);
}

int	finder(char *str, char checker)
{
	int	index;
	int	count;

	index = -1;
	count = 0;
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

	index = -1;
	if (str == '(')
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
