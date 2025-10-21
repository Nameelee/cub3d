/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:34:01 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/30 22:25:55 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief finds the player position in the map
 * @param map the char ** containing the map
 * @param x where to write the x position of the player
 * @param y where to write the y position of the player
 * @return 1 if the player pos was found else 0
 */
int	find_player_pos(char **map, int *x, int *y)
{
	*y = 0;
	while (map[*y])
	{
		*x = 0;
		while (map[*y][*x])
		{
			if (map[*y][*x] == 'N' || map[*y][*x] == 'S' || map[*y][*x] == 'E'
				|| map[*y][*x] == 'W')
				return (1);
			*x += 1;
		}
		*y += 1;
	}
	return (0);
}
