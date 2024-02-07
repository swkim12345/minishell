/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:52:54 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/07 14:22:37 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
/*
||, && 처리는 lexar에서 처리가 완료된 것으로 가정함.
*/

t_ast_node	*parser(char *input)
{
	t_ast_node	*head;
	
	head = lexar(input);
	//split with space
	
	//splitting
	//merge
}
