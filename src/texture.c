#include "../headers/cub3d.h"

void init_color(t_game *game)
{
	if (game->map_data.ceiling_color)
	{
		game->ceiling_color_int = create_trgb(0, game->map_data.ceiling_color->r,
				game->map_data.ceiling_color->g, game->map_data.ceiling_color->b);
	}
	if (game->map_data.floor_color)
	{
		game->floor_color_int = create_trgb(0, game->map_data.floor_color->r,
				game->map_data.floor_color->g, game->map_data.floor_color->b);
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	put_pixel_to_image(t_img *buffer, int x, int y, int color)
{
	char	*dst;

	dst = (char *)buffer->data + (y * buffer->size_l + x * (buffer->bpp / 8));
	*(unsigned int *)dst = color;
}

void	load_textures(t_game *game)
{
	int		width;
	int		height;
	char	*paths[4];

	paths[0] = game->map_data.wall_n_t;
	paths[1] = game->map_data.wall_s_t;
	paths[2] = game->map_data.wall_w_t;
	paths[3] = game->map_data.wall_e_t;
	for (int i = 0; i < 4; i++)
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
	}
}

void	draw_textured_line(t_game *game, t_ray *ray, int x)
{
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_to_image(&game->screen_buffer, x, y, game->ceiling_color_int);
		y++;
	}
	y = ray->draw_end;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel_to_image(&game->screen_buffer, x, y, game->floor_color_int);
		y++;
	}
	step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2)
		* step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = game->textures[ray->tex_num]
			.data[TEX_HEIGHT * tex_y + ray->tex_x];
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel_to_image(&game->screen_buffer, x, y, color);
		y++;
	}
}