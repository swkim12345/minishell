/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:22:56 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/21 12:27:23 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//lexar

//환경변수 들어올 경우 변환 필요, 
int		count_redirect(t_ast_node *node, t_minishell *minishell)
{
		//	if (ptr[index] == '<' || ptr[index] == '>')
		//{
		//	if (ptr[index] == ptr[index + 1])
		//		index += 1;
		//	index += 1;
		//	minishell->tmp_file_counter++;
		//}
}

//check redirection, ()
int		lexar(t_ast_node *node, char *ptr, t_minishell *minishell)
{
	int			index;
	int			str_flag;
	int			tmp;
	char		*dup_str;
	
	index = -1;
	str_flag = FALSE;
	while (++index)
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
	}
	//change
}
