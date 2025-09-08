/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:28:33 by manuelma          #+#    #+#             */
/*   Updated: 2025/08/13 17:45:17 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_cnt(char const *s, char c)
{
	int	output;

	output = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			output++;
		while (*s != c && *s)
			s++;
	}
	return (output);
}

static int	word_fill(char const *s, char c, char **output)
{
	int	len;
	int	wc;

	wc = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		len = 0;
		while (*s != c && *s)
		{
			s++;
			len++;
		}
		if (len > 0)
		{
			output[wc] = malloc((len + 1) * sizeof(char));
			if (!output[wc])
				return (++wc);
			output[wc] = ft_memcpy(output[wc], s - len, len);
			output[wc++][len] = '\0';
		}
	}
	output[wc] = NULL;
	return (0);
}

static void	ft_free(char ***tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		n_free((void **)&(*tab[i]));
		tab[i] = NULL;
		i++;
	}
	n_free((void **)tab);
	tab = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**output;
	int		word_count;
	int		i;

	output = NULL;
	word_count = words_cnt(s, c);
	output = malloc((word_count + 1) * sizeof(char **));
	if (!output)
		return (NULL);
	i = 0;
	while (i < word_count + 1)
		output[i] = NULL;
	word_count = word_fill(s, c, output);
	if (word_count)
	{
		ft_free(&output, word_count);
		return (NULL);
	}
	return (output);
}
/*
//test
#include <stdio.h>

int	main(int ac, char **av)
{
	char	**splited;
	int		word_count;
	int		i;

	if (ac == 3)
	{
		word_count = words_cnt(av[1], *av[2]);
		printf("nbr de mots:%d\n", word_count);
		splited = ft_split(av[1], *av[2]);
		i = 0;
		while (i < word_count)
		{
			printf("%s\n", splited[i]);
			i++;
		}

	}
}
*/
