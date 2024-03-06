/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser_env_var.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:11:32 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/06 22:11:43 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	parse_env_var_noquote(t_str_list *str_list,
		t_parse_str *parse_str, char *substitude_name)
{
	while (*substitude_name && ft_isspace(*substitude_name))
		substitude_name++;
	while (*substitude_name && !ft_isspace(*substitude_name))
	{
		append_char(parse_str, *substitude_name);
		substitude_name++;
	}
	if (*substitude_name)
	{
		add_string_node(str_list, parse_str);
		init_parse_str(parse_str);
	}
}

void	parse_env_var_found(t_str_list *str_list, t_parse_str *parse_str,
	char *substitude_name, int start_index)
{
	parse_str->cursor = start_index;
	if (parse_str->quote_flag)
	{
		while (*substitude_name)
		{
			append_char(parse_str, *substitude_name);
			substitude_name++;
		}
	}
	else
	{
		while (*substitude_name)
			parse_env_var_noquote(str_list, parse_str, substitude_name);
	}
}

void	parse_env_var(t_str_list *str_list, t_parse_str *parse_str,
	char **str, t_minishell *minishell)
{
	char	*env_name;
	char	*substitude_name;
	size_t	start_index;

	start_index = parse_str->cursor;
	append_char(parse_str, '$');
	while (**str && !ft_isspace(**str) && (!parse_str->quote_flag
			|| **str != '\"') && **str != '$' && **str != '\"' && **str != '\''
		&& **str != '/' && **str != '|')
		parse_single_char(str_list, parse_str, str, minishell);
	if (parse_str->cursor == start_index + 1)
		return ;
	env_name = ft_substr(parse_str->str, start_index + 1, parse_str->cursor);
	substitude_name = ft_getenv(minishell->env, env_name);
	free(env_name);
	if (!substitude_name)
	{
		parse_str->cursor = start_index;
		parse_str->str[start_index] = 0;
		return ;
	}
	parse_env_var_found(str_list, parse_str, substitude_name, start_index);
}
