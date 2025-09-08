/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 01:16:43 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/09 01:26:53 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief gets the first char that is not 'isspace'
 * @param str the string we want to skip all 'isspace'
 * return int with the index of the first non 'isspace' char or -1 if there
 * is only 'isspace' char in str
 */
int	get_index_after_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\f' && str[i] != '\n' \
			&& str[i] != '\r' && str[i] != '\t' && str[i] != '\v')
			return (i);
		i++;
	}
	return (-1);
}
