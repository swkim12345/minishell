#include "../main.h"

void	init_shell(t_minishell *shell)
{
	shell->cwd = getcwd(0, 0);
	shell->input_str = 0;
}

void	exit_handle(t_minishell *shell)
{
	free(shell->input_str);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int	str_equal(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (!*s1 && !*s2)
		return (1);
	return (0);
}


int	main()
{
	t_minishell	shell;
	t_ast_node	*head;

	system("leaks minishell");

	init_shell(&shell);
	while (1)
	{
		shell.input_str = readline("minishell-1.0$ ");
		if (!shell.input_str)
			exit_handle(&shell);
		else if (str_equal(shell.input_str, "exit"))
			exit_handle(&shell);
		head = lexar(shell.input_str);
		printf("%s\n", head->cmd_node->str[0]);
		//list = traverse(head);
		//printf("%s\n", list->node->cmd_node->str);
		// else
		// 	process_input(&shell);
		add_history(shell.input_str);
		free(shell.input_str);
	}
	return (0);
}
