/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:14:22 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/09 01:09:46 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

void	ft_bzero(void *s, size_t n)
{
	void	*a;

	a = s;
	while (n--)
	{
		*(char *)a = 0;
		a++;
	}
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	i;

	len_dst = ft_strlen_gnl(dst);
	i = 0;
	if (size <= len_dst)
		return (size + ft_strlen_gnl(src));
	while (++i < (size - len_dst) && src[i - 1])
		dst[len_dst + i - 1] = src[i - 1];
	dst[len_dst + i - 1] = '\0';
	return (len_dst + ft_strlen_gnl(src));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen_gnl(src);
	if (dstsize > 0)
	{
		dstsize--;
		while (dstsize-- > 0 && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (len);
}

char	*read_new_line(int fd, char *buffer, char *output, ssize_t *i)
{
	char	*temp;

	while (!ft_strchr(output, '\n'))
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		*i = read(fd, buffer, BUFFER_SIZE);
		if (*i > 0)
		{
			temp = ft_strjoin(output, buffer);
			free(output);
			output = ft_strdup(temp);
			free(temp);
		}
		else
		{
			if (!output || !*output || *i == -1)
				return (free(output), NULL);
			return (output);
		}
	}
	temp = ft_strchr(output, '\n');
	*(temp + 1) = '\0';
	return (output);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	char		*output;
	char		*temp;
	ssize_t		i;

	if (BUFFER_SIZE < 1 || BUFFER_SIZE > SIZE_MAX || fd < 0)
		return (NULL);
	i = 0;
	output = NULL;
	temp = NULL;
	if (*buffer[fd])
	{
		temp = ft_strchr(buffer[fd], '\n');
		if (temp)
		{
			i = temp - buffer[fd] + 1;
			output = ft_substr(buffer[fd], i, BUFFER_SIZE - i);
		}
		ft_bzero(buffer[fd], BUFFER_SIZE + 1);
		ft_strlcpy(buffer[fd], output, BUFFER_SIZE);
	}
	output = read_new_line(fd, buffer[fd], output, &i);
	if (!i)
		return (output);
	return (output);
}
