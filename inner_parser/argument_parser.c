/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:05:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 15:46:09 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	parse_single_char(t_str_list *str_list, t_parse_str *parse_str,
			char **str, t_minishell *minishell)
{
	if (**str)
	{
		if (**str == '\\' && (*str)[1] == '\\')
			(*str) += 1;
		else if (**str == '\\' && (*str)[1] == '\0')
		{
			(*str)++;
			return ;
		}
		else if (**str == '\\')
			(*str)++;
		else if (parse_str->quote_flag == FALSE && **str == '*'
			&& parse_str->asterisk_flag == -1)
			parse_str->asterisk_flag = 1;
		else if (**str == '$')
		{
			parse_dollar_sign(str_list, parse_str, str, minishell);
			return ;
		}
		append_char(parse_str, **str);
		*str = *str + 1;
	}
}

static void	parse_question_mark(t_parse_str *parse_str, char **str,
	t_minishell *minishell)
{
	char	*exit_status;
	int		i;

	exit_status = ft_itoa(minishell->exit_code);
	i = 0;
	while (exit_status[i])
	{
		append_char(parse_str, exit_status[i]);
		i++;
	}
	free(exit_status);
	(*str)++;
}

void	parse_dollar_sign(t_str_list *str_list, t_parse_str *parse_str,
			char **str, t_minishell *minishell)
{
	(*str)++;
	if (**str == '\"' && parse_str->quote_flag == FALSE)
		parse_double_quote(str_list, parse_str, str, minishell);
	else if (**str == '\'' && parse_str->quote_flag == FALSE)
		parse_single_quote(parse_str, str);
	else if (**str == '?')
		parse_question_mark(parse_str, str, minishell);
	else
		parse_env_var(str_list, parse_str, str, minishell);
}

void	parse_single_quote(t_parse_str *parse_str, char **str)
{
	parse_str->quote_flag = 1;
	(*str)++;
	while (**str && **str != '\'')
	{
		parse_str->asterisk_flag = 0;
		append_char(parse_str, **str);
		(*str)++;
	}
	(*str)++;
}

void	parse_double_quote(t_str_list *str_list, t_parse_str *parse_str,
			char **str, t_minishell *minishell)
{
	parse_str->quote_flag = 1;
	(*str)++;
	while (**str && **str != '\"')
	{
		parse_str->asterisk_flag = 0;
		parse_single_char(str_list, parse_str, str, minishell);
	}
	(*str)++;
}
