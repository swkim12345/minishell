/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:22:56 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/27 12:53:59 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

////lexar
//static int	lexar_file_parser(t_ast_node *node, t_redirection *red, int index)
//{

//}

//trim redirection
// shift index, error found : NOTDEFINED
static char	*lexar_redirect(t_ast_node *node, int index, t_minishell *minishell)
{
	char		*ptr;
	char		*file_name;
	t_redirection	*red;

	ptr = node->cmd_node->str[0]; //
	red = (t_redirection *)malloc(sizeof(t_redirection));
	ft_memset((void *)red, 0, sizeof(t_redirection));
	if (node->red == NULL)
		node->red = red;
	else
		node->red->next = red;
	if (ptr[index] == '<')
	{
		ptr[index] = '\0';
		if (ptr[index + 1] == '<')
		{
			red->flag = DB_LT_SIGN;
			index++;
		}
		else
			red->flag = LT_SIGN;
	}
	else
	{
		ptr[index] = '\0';
		if (ptr[index + 1] == '>')
		{
			red->flag = DB_GT_SIGN;
			index++;
		}
		else
			red->flag = GT_SIGN;
	}
	index++;
	ptr = ft_strjoin(ptr, ptr[index--]);
	free_doub_char(node->cmd_node->str);
	if (red->flag == DB_LT_SIGN || red->flag == DB_GT_SIGN)
		index--;
	//next token to redirection -> file name
	//not expend *
	//expend $
	//discard "", ''
	//error in ()
	//find next token
	ptr = node->cmd_node->str[0];
	while (ptr[index])
	{
		index += skip_space(&ptr[index]);
		if (ptr[index] == '$')
		{
			file_name = ft_getenv(minishell->env, &ptr[index + 1]);
			if (file_name == NULL)
				return (syntax_err_message(ptr, index, -1, minishell));
			break ;
		}
		
	}
	//strdup filename and strjoin node str
	red->str = ft_strdup(file_name);
	node->cmd_node->str = init_doub_char(&ptr, 1);
	free(ptr);
	//return function success
	//or return function failed
	return (FUNC_SUC);
}

//check redirection, ()
int	lexar(t_ast_node *node, t_minishell *minishell)
{
	char		*ptr;
	int			index;
	int			str_flag;
	int			tmp;
	
	index = -1;
	str_flag = FALSE;
	ptr = node->cmd_node->str[0];
	while (ptr[++index])
	{
		//skip discard token
		index += skip_space(&ptr[index]);
		if (ptr[index] == '\"' || ptr[index] == '\'')
		{
			tmp = finder(&ptr[index + 1], ptr[index]);
			if (tmp == NOTDEFINED)
				return (syntax_err_message(ptr, index, -1, minishell));
			index += tmp;
			continue ;
		}
		//check for redirection
		if (ptr[index] == '<' || ptr[index] == '>')
		{
			if (lexar_redirect(node, index, minishell))
			{
				return (syntax_err_message(ptr, index, -1, minishell));
			}
			index = -1;
			ptr = node->cmd_node->str[0];
			continue ;
		}
		//check for subshell
		if (ptr[index] == '(')
		{
			if (str_flag == FALSE) //trim bracket and recurv in subshell
			{
				tmp = bracket_finder(&ptr[index]);
				if (tmp == NOTDEFINED)
					return (NOTDEFINED);
				ptr[tmp + index] = ' ';
				ptr[index] = ' ';
				recurv_parser(node, minishell);
				continue ;
			}
			tmp = bracket_finder(&ptr[index]);
			if (tmp == NOTDEFINED)
				return (NOTDEFINED);
			tmp += skip_space(&ptr[index + tmp]);
		}
	}
	//use inner parser to parse subshell
}
