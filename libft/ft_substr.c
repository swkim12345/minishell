/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:38:26 by minsepar          #+#    #+#             */
/*   Updated: 2023/12/15 17:55:51 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*s_cpy;
	size_t	s_len;

	if (!s)
		return (0);
	while (*s && start > 0)
	{
		start--;
		s++;
	}
	s_len = ft_strlen(s);
	if (s_len < len)
		len = s_len;
	s_cpy = (char *)malloc(len + 1);
	if (!s_cpy)
		return (0);
	i = 0;
	while (s[i] && i < len)
	{
		s_cpy[i] = s[i];
		i++;
	}
	s_cpy[i] = 0;
	return (s_cpy);
}
