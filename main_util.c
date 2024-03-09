/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:28:05 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/09 12:12:38 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*color_add_minishell(char *input, char *color)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strdup(input);
	ret = ft_strjoin(color, tmp);
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(tmp, RESET);
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(tmp, "$ ");
	free(tmp);
	return (ret);
}

void	init_shell(t_minishell *shell, char **envp, char **argv, int argc)
{
	(void) argc;
	ft_memset(shell, 0, sizeof(t_minishell));
	shell->stdin_fd = dup(0);
	shell->stdout_fd = dup(1);
	shell->cwd = getcwd(0, 0);
	shell->envp = envp;
	shell->tmp_file_name = "/tmp/minishell_tmp_";
	shell->env = ft_initenv(envp, shell);
	shell->export = ft_initenv(envp, shell);
	if (ft_strncmp(argv[0], "./", 2) == 0)
		shell->execute_name = ft_substr(argv[0], 2, ft_strlen(argv[0]));
	else
		shell->execute_name = ft_strdup(argv[0]);
	shell->print_str = color_add_minishell(shell->execute_name, BOLD_BLUE);
	shell->tmp_list = (t_tmp_list *)ft_calloc(sizeof(t_tmp_list), 1);
	shell->flag = 0;
	set_signal_handler();
	set_term();
}

void	free_t_minishell(t_minishell *shell)
{
	(void) shell;
	free(shell->input_str);
	free(shell->cwd);
	free(shell->execute_name);
	free(shell->print_str);
	free_tmp_list(shell->tmp_list, shell, TRUE);
	free_tree_delete(shell->env);
	free_tree_delete(shell->export);
}

void	exit_handle(t_minishell *shell, int status)
{
	(void) shell;
	free_t_minishell(shell);
	ft_printf("exit\n");
	exit(status);
}

void	set_term(void)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}
