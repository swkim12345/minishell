/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:27 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/28 19:08:55 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_shell(t_minishell *shell, char **envp, char **argv)
{
	shell->cwd = getcwd(0, 0);
	shell->input_str = 0;
	shell->envp = envp;
	shell->tmp_file_name = "/tmp/minishell_tmp_";
	shell->tmp_file_counter = 0;
	shell->env = ft_initenv(envp, shell);
	shell->export = ft_initenv(envp, shell);
	if (ft_strncmp(argv[0], "./", 2) == 0)
		shell->execute_name = ft_substr(argv[0], 2, ft_strlen(argv[0]));
	else
		shell->execute_name = ft_strdup(argv[0]);
}

void	free_t_minishell(t_minishell *shell)
{
	(void) shell;
	free(shell->input_str);
	free(shell->cwd);
	free(shell->execute_name);
	free_tree_delete(shell->env);
	free_tree_delete(shell->export);
}

void	exit_handle(t_minishell *shell, int status)
{
	(void) shell;
	free_t_minishell(shell);
	printf("exit\n");
	exit(status);
}

void	set_term(void)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

void	check()
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	// atexit(check);
	t_minishell	shell;
	t_cmd_node	cmd_node;

	// atexit(check);
	init_shell(&shell, envp, argv);
	set_signal_handler();
	set_term();
	(void) argc;
	(void) argv;
	(void) cmd_node;

	// int i = 0;
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	// while (1)
	// {
	// 	shell.input_str = readline("minishell-1.0$ ");
	// 	if (!shell.input_str)
	// 		exit_handle(&shell, 134);
	// 	cmd_node.str = ft_split(shell.input_str, ' ');
	// 	cmd_node.cmd_name = cmd_node.str[0];
	// 	if (!shell.input_str)
	// 		exit_handle(&shell, EXIT_SUCCESS);
	// 	else if (ft_strlen(shell.input_str) > 0)
	// 		process_command(&cmd_node, &shell);
	// 	if (ft_strlen(shell.input_str) != 0)
	// 		add_history(shell.input_str);
	// 	free(shell.input_str);
	// 	free_2d_str(cmd_node.str);
	// }

	t_ast_node	*head;

	char *str[] = {"echo", "hello", NULL};

	
	printf("start----------------------------------\n");
	traverse(head, &shell, 1);
}
