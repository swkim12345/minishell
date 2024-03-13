/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_extern_command2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:39:43 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/13 15:34:15 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	process_extern_cmd_no_slash(t_cmd_node *cmd_node,
	t_minishell *minishell, char **envp)
{
	char	*execute_path;

	if (ft_strncmp(cmd_node->cmd_name, "", 1) == 0)
		command_not_found_error(minishell, cmd_node->cmd_name);
	execute_path = find_from_path(cmd_node, minishell);
	check_file_valid(execute_path, cmd_node, minishell);
	if (execve(execute_path, cmd_node->str, envp) == -1)
		shell_error(minishell, cmd_node->cmd_name, cmd_node->str[1]);
}
