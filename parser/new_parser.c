/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:46:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/20 18:53:12 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"
t_ast_node	*init_ast_node(int child_node)
{
	t_ast_node	*ret;
	t_cmd_node	*node;

	ret = (t_ast_node *)malloc(sizeof(t_ast_node));
	ft_memset((void *)ret, 0, sizeof(t_ast_node));
	ret->red = (t_redirection *)malloc(sizeof(t_redirection));
	ft_memset((void *)ret->red, 0, sizeof(t_redirection));
	ret->red->flag = NOTDEFINED;
	if (CMDNODE & child_node)
	{
		node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
		ft_memset((void *)node, 0, sizeof(t_cmd_node));
		ret->cmd_node = node;
	}
	if (LEFTNODE & child_node)
		ret->left_node = init_ast_node(CMDNODE);
	if (RIGHTNODE & child_node)
		ret->right_node = init_ast_node(CMDNODE);
	return (ret);
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


//in libft 구현
size_t	ft_strspn(const char *str, const char *accept)
{
	char	*p;
	char	*a;
	size_t	count;

	count = 0;
	p = (char *)str;
	a = (char *)accept;
	while (*p)
	{
		while (*a)
		{
			if (*p == *a)
				break ;
			a++;
		}
		if (!*a)
			return (count);
		else
			count++;
		p++;
	}
	return (count);
}

char	*ft_strtok(char *str, const char *delim)
{
	char	*next_token;

	if (!str)
		next_token = str;
	next_token += ft_strspn(next_token, delim);
	if (!*next_token)
		return (NULL);
	return (next_token);
}


int	finder(char *str, char *checker)
{
	
}



char	*dup_str(char *str, int start, int end)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (end - start + 1));
	ret[end - start] = '\0';
	ft_memmove((void *)ret, (void *)&str[start], end - start);
	return (ret);
}

//error 시 -1 리턴
int		bracket_finder(char *str)
{
	int	count;

	
}

int		bracket_parser(char *str, int index, int str_flag, t_minishell *minishell)
{
	char	*ptr;
	
	ptr = &str[index];
	if (*ptr == '(')
	{
		if (str_flag == TRUE)
		{
			index += find_bracket(ptr);
			return(syntax_err_message(ptr, index, -1, minishell));
		}
		else
		{
			index += find_bracket(ptr);
		}
	}
	return (index);
}

static int		split_recurv_parser(t_ast_node *head, int str_end, int dup_str_start, t_minishell *minishell)
{
	char	*ptr;
	int		size;
	int		tmp;

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
	int		size;
	int		str_flag;
	int		bracket_flag;
	int		tmp;
	char	*ptr;

	index = -1;
	ptr = head->cmd_node->str[0];
	size = ft_strlen(ptr);
	str_flag = FALSE;
	bracket_flag = FALSE;
	while (ptr[++index])
	{	
		index += skip_space(&ptr[index]);
		if (ptr[index] == '\"' || ptr[index] == '\'')
		{
			index = index + ft_strtok(&ptr[index], ptr[index]) - ptr;
			continue ;
		}
		if (ptr[index] == '(')
		{
			tmp = bracket_parser(ptr, index, str_flag, minishell);
			if (tmp == -1)
				return (FUNC_FAIL);
			index += tmp;
			continue ;
		}
		if (ptr[index] == '|' && ptr[index + 1] == '|')
		{
			tmp = split_recurv_parser(head, index - 1, index + 2, minishell);
			return (tmp);
		}
		if (ptr[index] == '&' && ptr[index + 1] == '&')
		{
			tmp = split_recurv_parser(head, index - 1, index + 2, minishell);
			return (tmp);
		}
		if (ptr[index] == '|')
		{
			tmp = split_recurv_parser(head, index - 1, index + 1, minishell);
			return (tmp);
		}
		//check for redirection
		//indexing required
		if (ptr[index] == '<')
		{
			if (ptr[index + 1] == '<')
			{
				//here_doc
				index += 2;
				index += skip_space(&ptr[index]);
				if ()
				head->left_node = init_ast_node(CMDNODE);
				recur_lexar(head->left_node);
			}
			else
			{
				//redirection
				//indexing required
			}
		}
		if (ptr[index] == '>')
		{
			if (ptr[index + 1] == '>')
			{
				//redirection
				//indexing required
			}
			else
			{
				//redirection
				//indexing required
			}
		}
		str_flag = TRUE;
	}
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
		free_ast_node(ret);
		return (NULL);
	}
	return (ret);
}
