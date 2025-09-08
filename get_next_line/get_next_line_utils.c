/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:58:18 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/08 23:29:06 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*output;

	len = ft_strlen_gnl(s1) + 1;
	output = malloc(sizeof(char) * (len));
	if (output == NULL)
		return (NULL);
	ft_strlcpy(output, s1, len);
	return (output);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*output;

	if (start >= (unsigned int)ft_strlen_gnl(s))
	{
		output = malloc(sizeof(char) * 1);
		if (!output)
			return (NULL);
		*output = '\0';
		return (output);
	}
	if (len > ft_strlen_gnl(s) - start)
		len = ft_strlen_gnl(s) - start;
	output = malloc(sizeof(char) * (len + 1));
	if (!output)
		return (NULL);
	ft_strlcpy(output, s + start, len + 1);
	return (output);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*output;

	len_s1 = ft_strlen_gnl(s1);
	len_s2 = ft_strlen_gnl(s2);
	output = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!output)
		return (NULL);
	ft_bzero(output, len_s1 + len_s2 + 1);
	ft_strlcat(output, s1, len_s1 + 1);
	ft_strlcat(output, s2, len_s2 + len_s1 + 1);
	return (output);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
