/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:16:31 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/07 17:17:25 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	**init_doub_char(char **input, int size)
{
	char	**ret;
	int		i;

	i = -1;
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	while (++i < size)
		ret[i] = input[i];
	ret[i] = NULL;
	return (ret);
}

void	free_doub_char(char **input)
{
	int	i;

	i = -1;
	while (input[++i])
		free(input[i]);
	free(input[i]);
	free(input);
}

void	free_cmd_node(t_cmd_node *node)
{
	t_cmd_node	*next_node;
	int	i;

	i = -1;
	if (node == NULL)
		return ;
	free_doub_char(node->str);
	free(node->cmd_name);
	free(node);
	free_cmd_node(next_node);
}

