/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:51:02 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/11 20:22:07 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

void	ft_bzero_gnl(void *s, size_t n);
size_t	ft_strlcat_gnl(char *dst, const char *src, size_t size);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);
int		ft_strlen_gnl(const char *str);
char	*ft_strdup_gnl(const char *s1);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*ft_strchr_gnl(const char *s, int c);

#endif