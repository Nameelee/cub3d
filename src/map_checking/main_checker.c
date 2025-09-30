/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:28:11 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/30 22:48:38 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief checks recursively that the map is valid with flood fill algorithm
 * @param map the map to check
 * @param x current x position
 * @param y current y position
 * @return SUCCESS if valid, ERR_INVALID_MAP if not
 */
int	recursive_map_check(char **map, int y, int x)
{
	map[y][x] = 'X';
	if (x == 0 || x == (int)(ft_strlen(map[y]) - 2)
		|| ft_isspace(map[y - 1][x]) || ft_isspace(map[y + 1][x])
		|| ft_isspace(map[y][x - 1]) || ft_isspace(map[y][x + 1]))
		return (ERR_INVALID_MAP);
	if (map[y - 1][x] == '0')
		if (recursive_map_check(map, y - 1, x) == ERR_INVALID_MAP)
			return (ERR_INVALID_MAP);
	if (map[y + 1][x] == '0')
		if (recursive_map_check(map, y + 1, x) == ERR_INVALID_MAP)
			return (ERR_INVALID_MAP);
	if (map[y][x - 1] == '0')
		if (recursive_map_check(map, y, x - 1) == ERR_INVALID_MAP)
			return (ERR_INVALID_MAP);
	if (map[y][x + 1] == '0')
		if (recursive_map_check(map, y, x + 1) == ERR_INVALID_MAP)
			return (ERR_INVALID_MAP);
	return (SUCCESS);
}

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
		i_char = -1;
		while (str[++i_char])
		{
			if (str[i_char] != '0' && str[i_char] != '1'
				&& !ft_isspace(str[i_char]))
			{
				if ((str[i_char] == 'N' || str[i_char] == 'S' || str[i_char]
						== 'E' || str[i_char] == 'W') && player_found == 0)
					player_found = 1;
				else
					return (0);
			}
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
	char	**temp_map;
	int		x;
	int		y;
	int		error;

	if (!map_has_only_valid_chars(map_data))
		return (ERR_MISS_OR_INVAL_PARAM);
	if (!isspace_or_one(map_data->map[0]))
		return (ERR_MISS_OR_INVAL_PARAM);
	if (!isspace_or_one(map_data->map[count_strs(map_data->map) - 1]))
		return (ERR_MISS_OR_INVAL_PARAM);
	temp_map = strs_dup(map_data->map);
	if (temp_map == NULL)
		return (ERR_MALLOC);
	x = 0;
	y = 0;
	find_player_pos(temp_map, &x, &y);
	error = recursive_map_check(temp_map, y, x);
	free_double((void ***)&temp_map);
	return (error);
}
