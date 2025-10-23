/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelee <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:34:46 by jelee             #+#    #+#             */
/*   Updated: 2025/10/17 13:34:51 by jelee            ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	init_map_data(t_map_data *map_data)
{
	map_data->ceiling_color = NULL;
	map_data->floor_color = NULL;
	map_data->wall_n_t = NULL;
	map_data->wall_s_t = NULL;
	map_data->wall_e_t = NULL;
	map_data->wall_w_t = NULL;
	map_data->map = NULL;
}

/**
*mlx_init initializes the connection to the operating system's 
graphical display server and returns a unique pointer 
(handle) to that connection
*mlx_new_image: it create invisible blank paepr in memory
	put_pixel_to_image draw pic here(memory buffer) to avoid flickering
*mlx_put_image_to_window <- this shoot the buffered image into window
*mlx_get_data_addr: it gets address of memory drawn by put_pixel_to_image
*/
int	init_all(t_game *game)
{
	init_player_position(game);
	init_color(game);
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		return (1);
	game->win_ptr = mlx_new_window
		(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (game->win_ptr == NULL)
		return (1);
	game->screen_buffer.img_ptr = mlx_new_image(game->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->screen_buffer.img_ptr)
		return (perror("Screen buffer creation failed"), 1);
	game->screen_buffer.data = (int *)mlx_get_data_addr
		(game->screen_buffer.img_ptr,
			&game->screen_buffer.bpp, &game->screen_buffer.size_l,
			&game->screen_buffer.endian);
	return (0);
}

void	init_color(t_game *game)
{
	if (game->map_data.ceiling_color)
	{
		game->ceiling_color_int = create_trgb(0,
				game->map_data.ceiling_color->r,
				game->map_data.ceiling_color->g,
				game->map_data.ceiling_color->b);
	}
	if (game->map_data.floor_color)
	{
		game->floor_color_int = create_trgb(0, game->map_data.floor_color->r,
				game->map_data.floor_color->g, game->map_data.floor_color->b);
	}
}

/** 
 * game->player.pos_x = x + 0.5;//to locate character in the center
game->map_data.map[y][x] = '0';//to inform this spot is free to walk
 * 
*/
void	init_player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_data.height)
	{
		x = 0;
		while (x < game->map_data.width)
		{
			if (ft_strchr("NSWE", game->map_data.map[y][x]))
			{
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				set_player_direction(game, game->map_data.map[y][x]);
				game->map_data.map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
