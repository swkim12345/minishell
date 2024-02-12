/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:52:54 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/12 20:08:07 by sunghwki         ###   ########.fr       */
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
	*/
	
}

t_ast_node	*parser(char *input)
{
	t_ast_node	*head;
	
	head = init_ast_node(CMDNODE);
	
}
