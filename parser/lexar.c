/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:22:56 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/26 16:41:05 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//lexar
static int	lexar_file_parser(t_ast_node *node, char *ptr, t_minishell *minishell)
{
	//not expend *
	//expend $
	//discard "", ''
	//error in ()
	
	//return next token index
	//or return NOTDEFINED
}

//trim redirection
// shift index, error found : NOTDEFINED
static int	lexar_redirect(t_ast_node *node, char *ptr, t_minishell *minishell)
{
	int			index;
	char	*str;
	int			tmp;
	t_redirection	*red;

	ptr = node->str;
	tmp = 1;
	red = (t_redirection *)malloc(sizeof(t_redirection));
	ft_memset((void *)red, 0, sizeof(t_redirection));
	if (node->red == NULL)
		node->red = red;
	else
		node->red->next = red;
	if (ptr[index] == '<')
	{
		if (ptr[index + 1] == '<') //heredoc
		{
			red->flag = DB_LT_SIGN;
			tmp++;
		}
		else
			red->flag = LT_SIGN;
	}
	else
	{
		if (ptr[index + 1] == '>') // >>
		{
			red->flag = DB_GT_SIGN;
			tmp++;
		}
		else
			red->flag = GT_SIGN;
	}
	//next token to redirection
	while (ptr[index + tmp] == '\0')
	{
		//skip space
		tmp += skip_space(&ptr[index + tmp]);
		//if dollar start
		
		//check discard token in "", '' not discard but add file name.
		if (ptr[index + tmp] == '\"' || ptr[index + tmp] == '\'')
		{
			tmp += finder(&ptr[index + tmp + 1], ptr[index + tmp]);
			if (tmp == NOTDEFINED)
				return (NOTDEFINED);
			tmp++;
			continue ;
		}
		//if () -> error
		if (ptr[index + tmp] == '(')
			return (syntax_err_message("(", index + tmp, NOTDEFINED, minishell));
		//if error token
		ft_strtok()
	}
	//delete redirection token
	return (FUNC_SUC);
}

//check redirection, ()
int	lexar(t_ast_node *node, char *ptr, t_minishell *minishell)
{
	int			index;
	int			str_flag;
	int			tmp;
	
	index = -1;
	str_flag = FALSE;
	while (++index)
	{
		index += skip_space(&ptr[index]);
		if expension_dollar_sign(ptr, &index, minishell) //dollar sign check
		{
			
		}
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
		//check for redirection
		if (ptr[index] == '<' || ptr[index] == '>')
		{
			if (lexar_redirect(node, index, minishell))
			{
				return (syntax_err_message(ptr, index, -1, minishell));
			}
		}
	}
	//use inner parser to parse subshell
}
