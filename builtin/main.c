#include "../main.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;
	t_cmd_node	*cmd_node;
	char		**ret;
	int			index;

	index = -1;
	(void)argc;
	(void)argv;

	//system("leaks a.out");
	//while (envp[++index])
	//{
	//	printf("%d : %s\n", index, envp[index]);
	//}

	index = -1;
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	ft_memset((void *)minishell, 0, sizeof(t_minishell));
	cmd_node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	ft_memset((void *)cmd_node, 0, sizeof(t_cmd_node));
	cmd_node->str = (char **)malloc(sizeof(char *) * 5);
	cmd_node->str[0] = ft_strdup("export");
	cmd_node->str[1] = ft_strdup("$TEST=firstTest");
	cmd_node->str[2] = ft_strdup("$TEST=");
	cmd_node->str[3] = ft_strdup("TEST=$TEST");
	cmd_node->str[4] = NULL;
	minishell->env = ft_initenv(envp, minishell);
	minishell->export = ft_initenv(envp, minishell);

	ft_export(cmd_node, minishell);
	//ft_env(minishell);
	//ft_export(NULL, minishell);
	//ft_unset(cmd_node, minishell);
	//ft_env(minishell);
	//index = -1;
	//ret = ft_charenv(minishell->env);
	//while (ret[++index])
	//{
	//	printf("%d : %s\n", index, ret[index]);
	//}
	//ret = ft_charenv(minishell->export);
	//index = -1;
	//while (ret[++index])
	//{
	//	printf("%d : %s\n", index, ret[index]);
	//}
	free_tree_delete(minishell->env);
	free_tree_delete(minishell->export);
	free_2d_str(cmd_node->str);
	free(cmd_node);
	free(minishell);
	return (0);
}


//test for exit function
//int main()
//{
//	int	pid;
//	pid_t	t;
//	char	*str[] = {"exit", "100000000000000000000000000"};
//	t_cmd_node	*cmd_node;
//	t_minishell mini;

//	pid = fork();
//	//parent
//	if (pid)
//		pid = wait(&pid);
//	else
//	{
//		cmd_node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
//		cmd_node->str = str;
//		ft_exit(cmd_node, &mini);
//	}
//	printf("parent : %d", pid);
//	return (0);
//}


////test environ function
//int	main(int argc, char **argv, char **envp)
//{
//	t_tree_head	*head;
//	t_tree_node	*tmp;
//	t_minishell	*minishell;
//	char		**ret;
//	char		*key;
//	char		*value;
//	int			index;

//	index = -1;
//	minishell = (t_minishell *)malloc(sizeof(minishell));
//	ft_memset((void *)minishell, 0, sizeof(minishell));
//	while (envp[++index])
//	{
//		printf("%d : %s\n", index, envp[index]);
//	}
//	minishell->env = char_to_tree(envp);
//	minishell->env = ft_initenv(envp);
//	minishell->export = ft_dup_tree(minishell->env);
//	//printf("head size : %ld\n", head->size);
//	//index = -1;
//	//while (envp[++index])
//	//{
//	//	parse_env(envp[index], &key, &value);
//	//	printf("key : %s, node value : %s, real value: %s\n",key, tree_search(head->head, &tmp, key)->value, value);
//	//}

//	//segfault
//	printf("TEST setenv return : %d\n", ft_setenv(head, "TEST", "test"));

//	ft_unsetenv(head, "TEST");
//	printf("test value : %s\n", ft_getenv(head, "TEST"));
//	ft_setenv(head, "TEST", "test1");
//	printf("test value : %s\n", ft_getenv(head, "TEST"));
//	ret = tree_to_char(head);
//	index = -1;
	
//	while (ret[++index])
//	{
//		printf("%d : %s\n", index, ret[index]);
//	}
//	return (0);
//}
