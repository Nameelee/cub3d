/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:28:11 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/30 20:07:43 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief checks that all chars in str are 1 or isspace
 * @param str the string to check
 * @return 1 if only '1' or 'isspace' are found, else 0
 */
int	isspace_or_one(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != '1' && !ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief checks that all chars in map are valid
 * @param map_data the structure containing the map
 * @return enum with error code
 */
int	map_has_only_valid_chars(t_map_data *map_data)
{
	int		i_char;
	int		i_str;
	int		player_found;
	char	*str;

	player_found = 0;
	i_str = 0;
	while (map_data->map[i_str])
	{
		str = map_data->map[i_str++];
		i_char = 0;
		while (str[i_char])
		{
			if (str[i_char] != '0' && str[i_char] != '1' && !ft_isspace(str[i_char]))
			{
				if ((str[i_char] == 'N' || str[i_char] == 'S' || str[i_char]
					== 'E' || str[i_char] == 'W') && player_found == 0)
					player_found = 1;
				else
					return (0);
			}
			i_char++;
		}
	}
	return (player_found);
}

/**
 * @brief checks that the map is valid
 * @param map_data the structure containing the map
 * @return enum with error code (SUCCESS if the map is valid)
 */
int	map_checker(t_map_data *map_data)
{
	if (!map_has_only_valid_chars(map_data))
		return (ERR_MISS_OR_INVAL_PARAM);
	if (!isspace_or_one(map_data->map[0]))
		return (ERR_MISS_OR_INVAL_PARAM);
	if (!isspace_or_one(map_data->map[count_strs(map_data->map) - 1]))
		return (ERR_MISS_OR_INVAL_PARAM);
	/* - Recursive check starting from player position:
		- replace current position by 'X'
		- if there is a 'isspace' up down left or right from current position -> map is not valid
		- relaunch recursive check in all '0' up down left or right from current position */
	return (SUCCESS);
}
