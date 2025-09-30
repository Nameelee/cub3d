/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:21:40 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/30 21:28:36 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * @brief duplicates a char ** with ft_str_dup
 * @param strs the char ** we want to duplicate
 * @return the duplicated char **
 */
char	**strs_dup(char **strs)
{
	int		size;
	int		i;
	char	**output;

	size = 0;
	while (strs[size])
		size++;
	output = malloc(sizeof(char *) * (size + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (i < size)
	{
		output[i] = ft_strdup(strs[i]);
		if (!output[i])
			return (free_double((void ***)&output), NULL);
		i++;
	}
	output[i] = NULL;
	return (output);
}
