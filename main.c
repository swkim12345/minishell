/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:27 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/05 18:00:52 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_shell(t_minishell *shell)
{
	shell->cwd = getcwd(0, 0);
	shell->input_str = 0;
}

int	main()
{
	t_minishell	shell;

	init_shell(&shell);
	while (1)
	{
		shell.input_str = readline("minishell-1.0$ ");
		add_history(shell.input_str);
	}
}