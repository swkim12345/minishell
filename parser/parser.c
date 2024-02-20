/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:46:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/20 22:16:30 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

//util, error
int		syntax_err_message(char *msg, int end, int ret, t_minishell *minishell)
{
	msg[end] = '\0';
	ft_putstr_fd(minishell->execute_name, STDERR_FILENO);
	ft_putstr_fd(": syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (ret);
}

char	*dup_str(char *str, int start, int end)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (end - start + 1));
	ret[end - start] = '\0';
	ft_memmove((void *)ret, (void *)&str[start], end - start);
	return (ret);
}

//lexar

int		count_redirect(char *ptr, t_minishell *minishell)
{
	int		index;
	int		bracket_flag;
	int		tmp;

	index = -1;
	bracket_flag = FALSE;
	while (++index)
	{
		//check for ()
		index += skip_space(&ptr[index]);
		if (ptr[index] == '(')
		{
			if (str_flag == TRUE)
				return (syntax_err_message(ptr, index, -1, minishell));
			tmp = bracket_parser(ptr, index, str_flag, minishell);
			if (tmp == NOTDEFINED)
				return (NOTDEFINED);
			tmp += skip_space(&ptr[index + tmp]);
		}
		//check for redirection
		if (ptr[index] == '<' || ptr[index] == '>')
		{
			if (bracket_flag == TRUE)
				return (syntax_err_message(ptr, index, -1, minishell));
			if (ptr[index] == ptr[index + 1])
				index += 1;
			index += 1;
			minishell->tmp_file_counter++;
		}
	}
}

//check redirection, ()
int		lexar(t_ast_node *head, char *str, t_minishell *minishell)
{
	char	*ptr;
	int		tmp;
	int		index;
	int		bracket_flag;

	ptr = head->cmd_node->str[0];
	index = -1;
	bracket_flag = FALSE;
	
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

//error 시 -1 리턴
int		bracket_finder(char *str)
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

//parser
int		bracket_parser(char *str, int index, int str_flag, t_minishell *minishell)
{
	char	*ptr;
	int		ret;
	
	ptr = &str[index];
	if (*ptr == '(')
	{
		if (str_flag == TRUE)
			return (syntax_err_message(ptr, index, -1, minishell));
		else
		{
			ret = bracket_finder(ptr);
			if (ret == NOTDEFINED)
				return (syntax_err_message(ptr, index, -1, minishell));
			else
				return (ret);
		}
	}
	return (index);
}

static int		split_recurv_parser(t_ast_node *head, int str_end, int dup_str_start, t_minishell *minishell)
{
	char	*ptr;
	int		size;
	int		tmp;

	if (str_end <= 0)
		return (syntax_err_message(ptr, dup_str_start, -1, minishell));
	ptr = head->cmd_node->str[0];
	size = ft_strlen(ptr);
	head->left_node = init_ast_node(CMDNODE);
	head->right_node = init_ast_node(CMDNODE);
	head->left_node->cmd_node->str = 
	init_doub_char(dup_str(ptr, 0, str_end), 1);
	head->right_node->cmd_node->str = 
	init_doub_char(dup_str(ptr, dup_str_start, size), 1);
	tmp = recur_lexar(head->left_node);
	if (tmp == FUNC_FAIL)
		return (FUNC_FAIL);
	tmp = recur_lexar(head->right_node);
	if (tmp == FUNC_FAIL)
		return (FUNC_FAIL);
	return (FUNC_SUC);
}

int		recurv_parser(t_ast_node *head, t_minishell *minishell)
{
	t_ast_node	*ret;
	int		index;
	int		str_flag;
	int		tmp;
	char	*ptr;

	index = -1;
	ptr = head->cmd_node->str[0];
	str_flag = FALSE;
	while (ptr[++index])
	{	
		index += skip_space(&ptr[index]);
		if (ptr[index] == '\"' || ptr[index] == '\'')
		{
			tmp = finder(&ptr[index + 1], ptr[index]);
			if (tmp == NOTDEFINED)
				return (syntax_err_message(ptr, index, -1, minishell));
			index += tmp;
			continue ;
		}
		if (ptr[index] == '(')
		{
			if (str_flag == TRUE)
				return (syntax_err_message(ptr, index, -1, minishell));
			tmp =  bracket_finder(&ptr[index + 1]);
			if (tmp == NOTDEFINED)
				return (tmp);
			index += tmp;
			continue ;
		}
		if (ptr[index] == '|' && ptr[index + 1] == '|')
			return (split_recurv_parser(head, index - 1, index + 2, minishell));
		if (ptr[index] == '&' && ptr[index + 1] == '&')
			return (split_recurv_parser(head, index - 1, index + 2, minishell));
		if (ptr[index] == '|')
			return (split_recurv_parser(head, index - 1, index + 1, minishell));
		str_flag = TRUE;
	}
	tmp = lexar(head, ptr, minishell);
	if (tmp == FUNC_FAIL)
		return (FUNC_FAIL);
	return (FUNC_SUC);
}

t_ast_node	*new_parser(char *str, t_minishell *minishell)
{
	t_ast_node	*ret;
	int			err;

	ret = init_ast_node(CMDNODE);
	ret->cmd_node->str = init_doub_char(&str, 1);
	err = recurv_parser(ret, minishell);
	if (err == FUNC_FAIL)
	{
		free_ast_tree(ret);
		return (NULL);
	}
	return (ret);
}
