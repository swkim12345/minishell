/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:46:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/20 19:27:02 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

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

int		recurv_parser(t_ast_node *head, t_minishell *minishell)
{
	t_ast_node	*ret;
	int		index;
	int		size;
	int		str_flag;
	int		bracket_flag;
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
			bracket_parser(ptr, index, str_flag, minishell);
		}
		if (ptr[index] == '|' && ptr[index + 1] == '|')
		{
			//recursive
			head->left_node = init_ast_node(CMDNODE);
			head->right_node = init_ast_node(CMDNODE);
			head->left_node->cmd_node->str = 
			init_doub_char(dup_str(ptr, 0, index - 1), 1);
			head->right_node->cmd_node->str = 
			init_doub_char(dup_str(ptr, index + 2, size), 1);
			recur_lexar(head->left_node);
			recur_lexar(head->right_node);
			
			break ;
		}
		if (ptr[index] == '&' && ptr[index + 1] == '&')
		{

			//recursive
			break ;
		}
		if (ptr[index] == '|')
		{
			//recursive
			break ;
		}
		//check for redirection
		str_flag = TRUE;
	}
	return (FUNC_SUC);
}



t_ast_node	*new_parser(char *str, t_minishell *minishell)
{
	t_ast_node	*ret;

	ret = init_ast_node(CMDNODE);
	ret->cmd_node->str = init_doub_char(&str, 1);
	ret = recurv_parser(ret, minishell);
	return (ret);
}
