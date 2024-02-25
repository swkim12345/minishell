#include "builtin.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;
	//char		**ret;
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
	//minishell = (t_minishell *)malloc(sizeof(t_minishell));
	//ft_memset((void *)minishell, 0, sizeof(t_minishell));
	//minishell->env = ft_initenv(envp);
	//minishell->export = ft_initenv(envp);
	//ft_env(minishell); //leaks 

	//free_tree_delete(minishell->env);
	//free_tree_delete(minishell->export);
	//free(minishell);
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
