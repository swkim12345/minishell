#include "environ.h"

int	main(int argc, char **argv, char **envp)
{
	t_tree_head	*head;
	t_tree_node	*tmp;
	t_minishell	*minishell;
	char		**ret;
	char		*key;
	char		*value;
	int			index;

	index = -1;
	minishell = (t_minishell *)malloc(sizeof(minishell));
	ft_memset((void *)minishell, 0, sizeof(minishell));
	//while (envp[++index])
	//{
	//	printf("%d : %s\n", index, envp[index]);
	//}
	head = char_to_tree(envp);
	//printf("head size : %ld\n", head->size);
	//index = -1;
	//while (envp[++index])
	//{
	//	parse_env(envp[index], &key, &value);
	//	printf("key : %s, node value : %s, real value: %s\n",key, tree_search(head->head, &tmp, key)->value, value);
	//}

	//segfault
	printf("TEST setenv return : %d\n", ft_setenv(head, "TEST", "test"));

	ft_unsetenv(head, "TEST");
	printf("test value : %s\n", ft_getenv(head, "TEST"));
	ft_setexport(head, "TEST", "test1");
	printf("test value : %s\n", ft_getenv(head, "TEST"));
	ret = tree_to_char(head);
	index = -1;
	
	while (ret[++index])
	{
		printf("%d : %s\n", index, ret[index]);
	}
	return (0);
}

