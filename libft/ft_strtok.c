/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:15:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/13 12:39:11 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *str, const char *accept)
{
	char	*p;
	char	*a;
	size_t	count;

	count = 0;
	p = str;
	a = accept;
	while (*p)
	{
		while (*a)
		{
			if (*p == *a)
				break ;
			a++;
		}
		if (!*a)
			return (count);
		else
			count++;
		p++;
	}
	return (count);
}

size_t	ft_strcspn(const char *str, const char *reject)
{
	char	*p;
	char	*r;
	size_t	count;

	count = 0;
	p = str;
	r = reject;
	while (*p)
	{
		while (*r)
		{
			if (*p == *r)
				return (count);
			r++;
		}
		count++;
		p++;
	}
	return (count);
}

char	*ft_strtok(char *str, const char *delim)
{
	char	*next_token;
	char	*tmp;

	if (!str)
		next_token = str;
	else
		return (NULL);
	next_token += ft_strspn(next_token, delim);
	if (!*next_token)
		return (NULL);
	tmp = next_token;
	next_token += ft_strcspn(next_token, delim);
	if (*next_token)
		*next_token++ = '\0';
	else
		next_token = NULL;
	return (tmp);
}
