/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:08:24 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/29 14:23:36 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * @brief returns the next index that is not a 'isspace' char
 * @param str the string to check
 * @param i the index after wich we search for the next char not 'isspace'
 * @return the next char not 'isspace' index
 */
int	next_index_after_isspace(char *str, int i)
{
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

/**
 * @brief returns the number of digits found before the first non-digit
 * @param str the string to check
 * @return the number of digits encountered
 */
int	cnt_digits(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && ft_isdigit(str[i]))
		i++;
	return (i);
}
