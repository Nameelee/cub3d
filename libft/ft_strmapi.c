/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:53:34 by manuelma          #+#    #+#             */
/*   Updated: 2025/08/13 16:19:55 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*output;

	output = NULL;
	len = (unsigned int)ft_strlen(s);
	output = malloc((len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	ft_bzero(output, len + 1);
	output[len] = '\0';
	i = 0;
	while (i < len)
	{
		output[i] = f(i, s[i]);
		i++;
	}
	return (output);
}
/*
//test
#include <stdio.h>

char increment_char_with_index(unsigned int i, char c)
{
	return(c + i);
}
int	main()
{
	char	str[5] = "aaaa";
	printf("result:%s", ft_strmapi(str, increment_char_with_index));
	return (0);
}
*/
