/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:22:56 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/29 14:37:40 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	lexar_redirect(t_ast_node *node, t_minishell *minishell, int index)
{
	char			*ptr;
	int				start;
	t_tmp_file		*tmp_file;
	t_redirection	*red;

	ptr = node->cmd_node->str[0]; 
	red = (t_redirection *)malloc(sizeof(t_redirection));
	tmp_file = NULL;
	ft_memset((void *)red, 0, sizeof(t_redirection));
	redirect_node_push(node, red);
	if (ptr[index] == '<')
	{
		ptr[index] = '\0';
		printf("ptr[%d]: %c\n", index, ptr[index]);
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
	start = index;
	index += skip_space(&ptr[index]);
	//syntax error newline
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
	
	red->str = ft_substr(&ptr[start + skip_space(&ptr[start])], 0, index - start);
	ft_strlcat(ptr, &ptr[index], ft_strlen(ptr) + ft_strlen(&ptr[index]) + 1);
	//printf("ptr after strlcat: %s\n", ptr);
	//printf("red->str: %s\n", red->str);
	
	if (red->flag == DB_LT_SIGN)
	{
		//add file name
		tmp_file = (t_tmp_file *)malloc(sizeof(t_tmp_file));
		ft_memset((void *)tmp_file, 0, sizeof(t_tmp_file));
		tmp_file->tmp = ft_strjoin(minishell->tmp_file_name, ft_itoa(minishell->tmp_file_counter));
		tmp_file->fd = open(tmp_file->tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (tmp_file->fd == -1) //add file descriptor error
			return (-2); //maybe leak inside
		red->index = minishell->tmp_file_counter;
		tmp_file_list_push(tmp_file, minishell);
		if (read_heredoc(minishell, red, tmp_file) != FUNC_SUC)
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
				recurv_parser(node, minishell);
				continue ;
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
	node->cmd_node->str = cmd_str;
	index = -1;
	while (cmd_str[++index])
		printf("cmd_str[%d]: %s\n", index, cmd_str[index]);
	return (FUNC_SUC);
}
