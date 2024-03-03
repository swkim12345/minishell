/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:22:56 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/03 12:54:39 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	heredoc_open_fd(t_redirection *red, t_minishell *minishell)
{
	t_tmp_file	*tmp_file;
	
	//add file name
	tmp_file = (t_tmp_file *)malloc(sizeof(t_tmp_file));
	ft_memset((void *)tmp_file, 0, sizeof(t_tmp_file));
	tmp_file->tmp = ft_strjoin(minishell->tmp_file_name, ft_itoa(minishell->tmp_file_counter));
	tmp_file->fd = open(tmp_file->tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmp_file->fd == -1) //add file descriptor error
		return (FUNC_SUC); //maybe leak inside
	red->index = minishell->tmp_file_counter;
	tmp_list_push(tmp_file, minishell);
	//if (read_heredoc(minishell, red, tmp_file) != FUNC_SUC)
	//	return (FUNC_FAIL);
	return (FUNC_SUC);
}

static int	find_next_token_red(char *ptr, int index, t_redirection *red)
{
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
	return (index);
}

static char *file_name_parser(char *ptr)
{
	t_parse_str	parse_str;
	char		*ret;
	int			index;

	init_parse_str(&parse_str);	
	index = -1;
	while (ptr[++index])
	{
		if (ft_isspace(ptr[index]) == TRUE)
			continue ;
		if (ptr[index] == '\"' || ptr[index] == '\'')
			continue ;
		append_char(&parse_str, ptr[index]);
	}
	ret = ft_strdup(parse_str.str); 
	free_parse_str(&parse_str);
	free(ptr);
	return (ret);
}

static int	lexar_redirect(t_ast_node *node, t_minishell *minishell, int index)
{
	char			*ptr;
	int				start;
	t_redirection	*red;

	ptr = node->cmd_node->str[0]; 
	red = (t_redirection *)malloc(sizeof(t_redirection));
	ft_memset((void *)red, 0, sizeof(t_redirection));
	redirect_node_push(node, red);
	index = find_next_token_red(ptr, index, red);
	start = index;
	index += skip_space(&ptr[index]);
	if (ptr[index] == '\0')
	{
		node->err_flag = TRUE;
		syntax_err_message("newline", NOTDEFINED, NOTDEFINED, minishell);
	}
	while (ptr[index] != '\0')
	{
		if (ft_isspace(ptr[index]) == TRUE || ptr[index] == '<' || ptr[index] == '>' || ptr[index] == '\0')
			break ;
		index++;
	}
	//printf("ptr: %s\n", ptr);
	//printf("ptr after index : %s\n", &ptr[index]);
	//printf("start: %d, index: %d\n", start, index);
	//printf("%s\n", &ptr[start]);
	red->str = ft_substr(&ptr[start], 0, index - start);
	red->str = file_name_parser(red->str);
	ft_strlcat(ptr, &ptr[index], ft_strlen(ptr) + ft_strlen(&ptr[index]) + 1);
	printf("ptr after strlcat: %s\n", ptr);
	printf("red->str: %s\n", red->str);
	printf("red->flag: %d\n", red->flag);
	if (red->flag == DB_LT_SIGN)
	{
		node->index = minishell->tmp_file_counter + 1;
		if (heredoc_open_fd(red, minishell) == FUNC_FAIL) //free add required
			return (-2);
	}
	if (red->flag == DB_LT_SIGN || red->flag == DB_GT_SIGN)
		return (start - 3);
	else
		return (start - 2);
}

//check redirection, ()
int	lexar(t_ast_node *node, t_minishell *minishell)
{
	char		*ptr;
	char		**cmd_str;
	int			index;
	int			str_flag;
	int			tmp;
	
	index = -1;
	str_flag = FALSE;
	ptr = node->cmd_node->str[0];
	printf("lexar ptr: %s\n", ptr);
	while (ptr[++index])
	{
		index += skip_space(&ptr[index]);
		if (ptr[index] == '\0')
			break ;
		if (ptr[index] == '\"' || ptr[index] == '\'')
		{
			tmp = finder(&ptr[index + 1], ptr[index]);
			if (tmp == NOTDEFINED)
				return (syntax_err_message(ptr, NOTDEFINED, -1, minishell));
			index += tmp + 1;
			continue ;
		}
		if (ptr[index] == '<' || ptr[index] == '>')
		{
			index = lexar_redirect(node, minishell, index);
			if (index == -2)
				return (syntax_err_message(ptr, index, -1, minishell));
			continue ;
		}
		if (ptr[index] == '(') // fix to check flag sign
		{
			if (str_flag == FALSE)
			{
				tmp = bracket_finder(&ptr[index]);
				if (tmp == NOTDEFINED)
					return (NOTDEFINED);
				ptr[tmp + index] = ' ';
				ptr[index] = ' ';
				return (recurv_parser(node, minishell));
			}
			tmp = bracket_finder(&ptr[index]);
			if (tmp == NOTDEFINED)
				return (NOTDEFINED);
			tmp += skip_space(&ptr[index + tmp]);
			str_flag = TRUE;
		}
	}
	cmd_str = string_parser(ptr, minishell);
	free_2d_str(node->cmd_node->str);
	//if (cmd_str[0][0] == '\0') //adhoc
	//{
	//	free(cmd_str[0]);
	//	cmd_str[0] = NULL;
	//}
	node->cmd_node->str = cmd_str;
	return (FUNC_SUC);
}
