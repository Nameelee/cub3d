/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rectangular.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelee <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:00:16 by jelee             #+#    #+#             */
/*   Updated: 2025/10/17 15:00:20 by jelee            ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Nami added. Takes a jagged 2D map and makes it rectangular.
 * @brief Each line in the new map is padded with spaces to match the
 * @brief maximum width. The original map is freed.
 * @param original_map The original map with uneven line lengths.
 * @param width The target width for the new rectangular map.
 * @param height The height of the map (number of lines).
 * @return A new, rectangular char ** map, or NULL on malloc failure.
 */
char	**regularize_map(char **original_map, int width, int height)
{
	char	**new_map;
	int		y;

	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	y = 0;
	while (y < height)
	{
		new_map[y] = malloc(sizeof(char) * (width + 1));
		if (!new_map[y])
		{
			free_double((void ***)&new_map);
			return (NULL);
		}
		ft_memset(new_map[y], ' ', width);
		ft_memcpy(new_map[y], original_map[y], ft_strlen(original_map[y]));
		new_map[y][width] = '\0';
		y++;
	}
	new_map[y] = NULL;
	free_double((void ***)&original_map);
	return (new_map);
}

/**
 * @brief Calculates map dimensions, regularizes the map, and checks for errors.
 * @param map_data The map data struct containing the initial map.
 * @return An error code, or SUCCESS if the map is valid.
 */
int	process_and_validate_map(t_map_data *map_data)
{
	int	error;

	map_data->height = 0;
	while (map_data->map[map_data->height])
		map_data->height++;
	map_data->width = get_map_width(map_data->map);
	map_data->map = regularize_map(map_data->map,
			map_data->width, map_data->height);
	if (!map_data->map)
		return (ERR_MALLOC);
	error = map_checker(map_data);
	return (error);
}
