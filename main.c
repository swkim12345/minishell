/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:27 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/26 20:00:19 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_shell(t_minishell *shell, char **envp)
{
	shell->cwd = getcwd(0, 0);
	shell->input_str = 0;
	shell->envp = envp;
	shell->tmp_file_name = "/tmp/minishell_tmp_";
	shell->tmp_file_counter = 0;
	shell->env = ft_initenv(envp);
	shell->export = ft_initenv(envp);
}

void	exit_handle(t_minishell *shell)
{
	free(shell->input_str);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

void	set_term(void)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_cmd_node	cmd_node;

	init_shell(&shell, envp);
	set_signal_handler();
	set_term();
	(void) argc;
	(void) argv;

	// int i = 0;
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	while (1)
	{
		shell.input_str = readline("minishell-1.0$ ");
		cmd_node.str = ft_split(shell.input_str, ' ');
		cmd_node.cmd_name = cmd_node.str[0];
		if (!shell.input_str)
			exit_handle(&shell);
		else if (str_equal(shell.input_str, "exit"))
			exit_handle(&shell);
		else if (ft_strlen(shell.input_str) > 0)
			process_command(&cmd_node, &shell);
		add_history(shell.input_str);
		free(shell.input_str);
		free_2d_str(cmd_node.str);
	}
}
