/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:52:54 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/12 23:38:50 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
/*
||, && 처리는 lexar에서 처리가 완료된 것으로 가정함.
*/

char		**parse_str(char *input)
{
	/*
	space, tab, newline
	redirection(>, >>, <, <<)
	$ (dollar sign) - 이거 구현해야 함?
	'', ""는 처리하지 않음.
	*/
	long	index;
	char	*ptr;
	char	**ret;

	index = 0;
	while (input[index])
	{
		ptr = &input[index];
		//check "", ''
		if (*ptr == SINGLEQUOT[0]
		|| *ptr == DOUBLEQUOT[0])
			{
				ptr += find_end_quote(ptr);
				if (!ptr)
					return (NULL);
			}
		//space
		//tab
		//newline
		if (*ptr == ' ' || *ptr == '	' || *ptr == '\n')
		{
			//split str
		}
	}
	return (index);
}

t_ast_node	*parser(char *input)
{
	t_ast_node	*head;
	
	head = init_ast_node(CMDNODE);
	
}
