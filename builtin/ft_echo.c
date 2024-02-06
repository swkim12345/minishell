/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:28:52 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/06 20:39:08 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include <stdio.h>

int		ft_isspace(int c)
{
	if (c >= 9 && c <= 12)
		return (1);
	if (c == 32)
		return (1);
	return (0);
}

void	free_parse_str(t_parse_str *parse_str)
{
	free(parse_str->str);
	parse_str->str = 0;
}

void	init_parse_str(t_parse_str *parse_str)
{
	parse_str->str = malloc(11);
	parse_str->str[10] = 0;
	parse_str->cursor = 0;
	parse_str->malloc_size = 10;
}

void	init_str_node(t_str_node *str_node)
{
	str_node->next = 0;
	str_node->str = 0;
}

void	init_str_list(t_str_list *str_list)
{
	str_list->head = 0;
	str_list->tail = 0;
	str_list->size = 0;
}

void	append_char(t_parse_str *parse_str, char c)
{
	char	*new_malloc;
	int		prev_size;

	if (parse_str->malloc_size == parse_str->cursor)
	{
		prev_size = parse_str->cursor;
		parse_str->malloc_size *= 2;
		new_malloc = malloc(parse_str->malloc_size + 1);
		while (prev_size--)
			new_malloc[prev_size] = parse_str->str[prev_size];
		free(parse_str->str);
		parse_str->str = new_malloc;
	}
	parse_str->str[parse_str->cursor] = c;
	parse_str->cursor++;
	parse_str->str[parse_str->cursor] = 0;
}

void	enqueue(t_str_list *str_list, t_str_node *str_node)
{
	if (!(str_list->head))
	{
		str_list->head = str_node;
		str_list->tail = str_node;
	}
	else
	{
		str_list->tail->next = str_node;
		str_list->tail = str_node;
	}
	str_list->size++;
}

t_str_node	*dequeue(t_str_list *str_list)
{
	t_str_node	*head;

	if (!(str_list->head))
		return (0);
	else
	{
		head = str_list->head;
		str_list->head = head->next;
		if (!(str_list->head))
			str_list->tail = 0;
	}
	str_list->size--;
	return (head);
}

void	parse_single_char(t_parse_str *parse_str, char **str)
{
	if (**str)
	{
		if (**str == '\\')
			(*str)++;
		append_char(parse_str, **str);
		*str = *str + 1;
	}
}

void	parse_double_quote(t_parse_str *parse_str, char **str)
{
	(*str)++;
	while (**str && **str != '\"')
		parse_single_char(parse_str, str);
	(*str)++;
}

void	parse_single_quote(t_parse_str *parse_str, char **str)
{
	(*str)++;
	while (**str && **str != '\'')
	{
		parse_single_char(parse_str, str);
	}
	(*str)++;
}

void	add_string_node(t_str_list *str_list, t_parse_str *parse_str)
{
	t_str_node	*str_node;

	str_node = malloc(sizeof(t_str_node));
	str_node->str = ft_substr(parse_str->str, 0, parse_str->cursor);
	free_parse_str(parse_str);
	enqueue(str_list, str_node);
}


void	parse_single_word(char **str, t_str_list *str_list)
{
	t_parse_str	parse_str;

	init_parse_str(&parse_str);
	while (**str && !ft_isspace(**str))
	{
		if (**str == '\"')
			parse_double_quote(&parse_str, str);
		else if (**str == '\'')
			parse_single_quote(&parse_str, str);
		else
			parse_single_char(&parse_str, str);
	}
	if (parse_str.cursor > 0)
		add_string_node(str_list, &parse_str);
}

char	**list_to_char_arr(t_str_list *str_list)
{
	char		**return_list;
	t_str_node	*node;
	int			i;

	i = 0;
	return_list = malloc(sizeof(char *) * (str_list->size + 1));
	return_list[str_list->size] = 0;
	while (str_list->size > 0)
	{
		node = dequeue(str_list);
		return_list[i] = node->str;
		free(node);
		i++;
	}
	return (return_list);
}

void	print_echo(char **str)
{
	int	i;
	
	i = -1;
	while (str[++i])
	{
		if (i != 0)
			printf(" ");
		printf("%s", str[i]);
	}
}

int ft_echo(char *str)
{
	t_str_list	str_list;

	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		parse_single_word(&str, &str_list);
	}
	// char **str_arr = list_to_char_arr(&str_list);
	print_echo(list_to_char_arr(&str_list));
	return (1);
}

int main()
{
    ft_echo("\\t");
}