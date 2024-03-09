/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_extern_command2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:39:43 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/08 12:51:59 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	process_extern_cmd_no_slash(t_cmd_node *cmd_node,
	t_minishell *minishell)
{
	char	*execute_path;

	if (ft_strncmp(cmd_node->cmd_name, "", 1) == 0)
		command_not_found_error(minishell, cmd_node->cmd_name);
	execute_path = find_from_path(cmd_node, minishell);
	check_file_valid(execute_path, cmd_node, minishell);
	if (execve(execute_path, cmd_node->str, minishell->envp) == -1)
		shell_error(minishell, cmd_node->cmd_name, cmd_node->str[1]);
}
