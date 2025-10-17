/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelee <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:26:28 by jelee             #+#    #+#             */
/*   Updated: 2025/10/17 16:26:30 by jelee            ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	draw_tile(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			put_pixel_to_image(&game->screen_buffer,
				x * MINIMAP_SCALE + j, y * MINIMAP_SCALE + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_background(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_data.height)
	{
		x = 0;
		while (x < game->map_data.width)
		{
			if (game->map_data.map[y][x] == '1')
				draw_tile(game, x, y, WALL_COLOR);
			else
				draw_tile(game, x, y, FLOOR_COLOR);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_player(t_game *game)
{
	double	start_x;
	double	start_y;
	int		y;
	int		x;

	start_x = (game->player.pos_x * MINIMAP_SCALE) - (PLAYER_SIZE / 2.0);
	start_y = (game->player.pos_y * MINIMAP_SCALE) - (PLAYER_SIZE / 2.0);
	y = 0;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		while (x < PLAYER_SIZE)
		{
			put_pixel_to_image(&game->screen_buffer,
				(int)(start_x + x), (int)(start_y + y), PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_player_dir(t_game *game)
{
	double	x_pos;
	double	y_pos;
	double	x_inc;
	double	y_inc;
	int		steps;

	x_pos = game->player.pos_x * MINIMAP_SCALE;
	y_pos = game->player.pos_y * MINIMAP_SCALE;
	x_inc = game->player.dir_x;
	y_inc = game->player.dir_y;
	steps = (int)(fmax(fabs(x_inc), fabs(y_inc)) * MINIMAP_SCALE);
	x_inc /= (steps / MINIMAP_SCALE);
	y_inc /= (steps / MINIMAP_SCALE);
	while (steps > 0)
	{
		put_pixel_to_image(&game->screen_buffer, (int)x_pos,
			(int)y_pos, PLAYER_COLOR);
		x_pos += x_inc;
		y_pos += y_inc;
		steps--;
	}
}

void	draw_minimap(t_game *game)
{
	draw_minimap_background(game);
	draw_minimap_player(game);
	draw_minimap_player_dir(game);
}
