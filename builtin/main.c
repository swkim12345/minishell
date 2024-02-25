#include "../main.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;
	t_cmd_node	*cmd_node;
	int			index;

	index = -1;
	(void)argc;
	(void)argv;
	(void)envp;
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
	cmd_node->str[1] = ft_strdup("TEST=test");
	cmd_node->str[2] = ft_strdup("TEST1=");
	cmd_node->str[3] = ft_strdup("TEST2");
	cmd_node->str[4] = NULL;
	minishell->env = ft_initenv(envp);
	minishell->export = ft_initenv(envp);
	ft_env(minishell);
	ft_export(NULL, minishell);
	ft_export(cmd_node, minishell);
	ft_env(minishell);
	ft_export(NULL, minishell);
	ft_unset(cmd_node, minishell);
	ft_env(minishell);
	free_tree_delete(minishell->env);
	free_tree_delete(minishell->export);
	free_doub_char(cmd_node->str);
	free(cmd_node);
	free(minishell);
	return (0);
}


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
