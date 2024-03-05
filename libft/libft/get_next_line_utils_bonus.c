/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:29:07 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/04 21:30:42 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	*ft_free(void **zmem1, void *mem2, void *mem3)
{
	if (zmem1)
	{
		free(*zmem1);
		*zmem1 = 0;
	}
	free(mem2);
	free(mem3);
	return (0);
}

void	*fd_deletenode(t_fd_node **front, int fd)
{
	t_fd_node	*cur;
	t_fd_node	*next;

	if (!front || !*front)
		return (0);
	cur = *front;
	next = cur->next;
	while (cur->next && cur->next->fd < fd)
	{
		cur = cur->next;
		next = cur->next;
	}
	if ((*front)->fd == fd)
	{
		ft_free((void **)&cur->str, cur, 0);
		*front = next;
	}
	else if (cur->next && cur->next->fd == fd)
	{
		cur->next = next->next;
		ft_free((void **)&next->str, next, 0);
	}
	return (0);
}

void	*ft_read_line_helper(t_fd_node *cur, t_fd_node **front, ssize_t *ret)
{
	ssize_t	temp_i;
	char	*temp;

	if (cur->word_size + BUFFER_SIZE > cur->size)
	{
		cur->size = (cur->size < BUFFER_SIZE) * (BUFFER_SIZE + cur->word_size)
			+ !(cur->size < BUFFER_SIZE) * (cur->size * 2);
		temp = (char *)malloc(cur->size + 1);
		if (!temp)
			return (fd_deletenode(front, cur->fd));
		temp_i = cur->word_size;
		while (temp_i-- > 0)
			temp[temp_i] = cur->str[temp_i];
		free(cur->str);
		cur->str = temp;
	}
	*ret = read(cur->fd, &cur->str[cur->word_size], BUFFER_SIZE);
	if (*ret < 0)
		return (fd_deletenode(front, cur->fd));
	return (cur);
}
