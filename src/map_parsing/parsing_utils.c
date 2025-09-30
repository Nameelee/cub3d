/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 01:16:43 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/30 19:04:16 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief copy of the function isspace (man isspace)
 * @param c the char we check
 * @return 1 if char is 'isspace' else 0
 */
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

/**
 * @brief gets the first char that is not 'isspace'
 * @param str the string we want to skip all 'isspace'
 * @return int with the index of the first non 'isspace' char
 */
int	get_index_after_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (i);
		i++;
	}
	return (i);
}
