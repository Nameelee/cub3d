/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelee <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:35:47 by jelee             #+#    #+#             */
/*   Updated: 2025/10/17 14:35:50 by jelee            ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	load_textures(t_game *game)
{
	int		width;
	int		height;
	char	*paths[4];
	int		i;

	paths[0] = game->map_data.wall_n_t;
	paths[1] = game->map_data.wall_s_t;
	paths[2] = game->map_data.wall_w_t;
	paths[3] = game->map_data.wall_e_t;
	i = 0;
	while (i < 4)
	{
		game->textures[i].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
				paths[i], &width, &height);
		if (game->textures[i].img_ptr == NULL)
		{
			printf("Error: Texture '%s' loading failed.\n", paths[i]);
			exit(1);
		}
		game->textures[i].data = (int *)mlx_get_data_addr(
				game->textures[i].img_ptr, &game->textures[i].bpp,
				&game->textures[i].size_l, &game->textures[i].endian);
		i++;
	}
}

static	void	draw_ceiling(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_to_image(&game->screen_buffer, x, y, game->ceiling_color_int);
		y++;
	}
}

static	void	draw_floor(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = ray->draw_end;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel_to_image(&game->screen_buffer, x, y, game->floor_color_int);
		y++;
	}
}

static	void	draw_wall_slice(t_game *game, t_ray *ray, int x)
{
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;

	step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2)
		* step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = game->textures[ray->tex_num].data[TEX_HEIGHT
			* tex_y + ray->tex_x];
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel_to_image(&game->screen_buffer, x, y, color);
		y++;
	}
}

void	draw_textured_line(t_game *game, t_ray *ray, int x)
{
	draw_ceiling(game, ray, x);
	draw_wall_slice(game, ray, x);
	draw_floor(game, ray, x);
}
