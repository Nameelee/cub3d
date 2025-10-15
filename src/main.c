#include "../headers/cub3d.h"

int		key_press_handler(int keycode, t_game *game);
int		key_release_handler(int keycode, t_game *game);
void	move_player(t_game *game);

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

void	put_pixel_to_image(t_img *buffer, int x, int y, int color)
{
	char	*dst;

	// 주소 오프셋을 계산하여 해당 위치에 색상 값을 씁니다.
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
		//mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, 0x808080);
		put_pixel_to_image(&game->screen_buffer, x, y, game->ceiling_color_int);
		y++;
	}
	y = ray->draw_end;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel_to_image(&game->screen_buffer, x, y, game->floor_color_int);
		//mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, 0x0000FF);
		y++;
	}
	step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = game->textures[ray->tex_num].data[TEX_HEIGHT * tex_y + ray->tex_x];
        if (ray->side == 1)
            color = (color >> 1) & 8355711;
		//mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
		put_pixel_to_image(&game->screen_buffer, x, y, color);
		y++;
	}
}

void draw_tile(t_game *game, int x, int y, int color)
{
    int i = 0;
    while (i < MINIMAP_SCALE)
    {
        int j = 0;
        while (j < MINIMAP_SCALE)
        {
			put_pixel_to_image(&game->screen_buffer, x * MINIMAP_SCALE + j, y * MINIMAP_SCALE + i, color);
            //mlx_pixel_put(game->mlx_ptr, game->win_ptr, x * MINIMAP_SCALE + j, y * MINIMAP_SCALE + i, color);
            j++;
        }
        i++;
    }
}

void draw_minimap(t_game *game)
{
    int y = 0;
    while (y < game->map_data.height)
    {
        int x = 0;
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

    double precise_player_x = game->player.pos_x * MINIMAP_SCALE;
    double precise_player_y = game->player.pos_y * MINIMAP_SCALE;
    double start_draw_x = precise_player_x - (PLAYER_SIZE / 2.0);
    double start_draw_y = precise_player_y - (PLAYER_SIZE / 2.0);

    y = 0;
    while (y < PLAYER_SIZE)
    {
        int x = 0;
        while (x < PLAYER_SIZE)
        {
			put_pixel_to_image(&game->screen_buffer, (int)(start_draw_x + x), (int)(start_draw_y + y), PLAYER_COLOR);
            //mlx_pixel_put(game->mlx_ptr, game->win_ptr, (int)(start_draw_x + x), (int)(start_draw_y + y), PLAYER_COLOR);
            x++;
        }
        y++;
    }
    double end_x = (game->player.pos_x * MINIMAP_SCALE) + game->player.dir_x * MINIMAP_SCALE;
    double end_y = (game->player.pos_y * MINIMAP_SCALE) + game->player.dir_y * MINIMAP_SCALE;
    double dx = end_x - (game->player.pos_x * MINIMAP_SCALE);
    double dy = end_y - (game->player.pos_y * MINIMAP_SCALE);
    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    double x_inc = dx / steps;
    double y_inc = dy / steps;
    double x_line = game->player.pos_x * MINIMAP_SCALE;
    double y_line = game->player.pos_y * MINIMAP_SCALE;
    int i = 0;
    while (i <= steps)
    {
		put_pixel_to_image(&game->screen_buffer, (int)x_line, (int)y_line, PLAYER_COLOR);
        //mlx_pixel_put(game->mlx_ptr, game->win_ptr, (int)x_line, (int)y_line, PLAYER_COLOR);
        x_line += x_inc;
        y_line += y_inc;
        i++;
    }
}

int	close_game(t_game *game)
{
    // 중요: 생성된 모든 이미지를 파괴합니다.
    for (int i = 0; i < 4; i++)
	{
        if (game->textures[i].img_ptr)
            mlx_destroy_image(game->mlx_ptr, game->textures[i].img_ptr);
    }
    if (game->screen_buffer.img_ptr)
	{
        mlx_destroy_image(game->mlx_ptr, game->screen_buffer.img_ptr);
	}
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	}
	// Linux에서는 mlx_destroy_display를 호출해주는 것이 좋습니다.
	#ifdef __linux__
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	#endif
	free_map_data(&game->map_data);
	printf("Window closed. Exiting program.\n");
	exit(0);
	return (0);
}

int	game_loop(t_game *game)
{
	t_ray	ray;
	int		x;

	move_player(game);

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray_data(game, &ray, x);
		perform_dda(game, &ray);
		calculate_wall_projection(game, &ray);
		draw_textured_line(game, &ray, x);
		x++;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->screen_buffer.img_ptr, 0, 0);
	return (0);
}

void set_player_direction(t_game *game, char direction)
{
    if (direction == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (direction == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (direction == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
	else if (direction == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
}

void init_player_position(t_game *game)
{
    int y = 0;
    while (y < game->map_data.height)
    {
        int x = 0;
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

void	free_map_data(t_map_data *map_data)
{
	n_free((void **)&map_data->wall_n_t);
	n_free((void **)&map_data->wall_s_t);
	n_free((void **)&map_data->wall_e_t);
	n_free((void **)&map_data->wall_w_t);
	n_free((void **)&map_data->ceiling_color);
	n_free((void **)&map_data->floor_color);
	free_double((void ***)&map_data->map);
}

void	print_error(int error)
{
	if (error == ERR_ARGS)
		ft_putstr_fd(MSG_ERR_ARGS, STDERR_FILENO);
	else if (error == ERR_READ)
		ft_putstr_fd(MSG_ERR_READ, STDERR_FILENO);
	else if (error == ERR_FILE_NAME)
		ft_putstr_fd(MSG_ERR_FILE_NAME, STDERR_FILENO);
	else if (error == ERR_MISS_OR_INVAL_PARAM)
		ft_putstr_fd(MSG_ERR_MISS_OR_INVAL_PARAM, STDERR_FILENO);
	else if (error == ERR_MALLOC)
		ft_putstr_fd(MSG_ERR_MALLOC, STDERR_FILENO);
	else if (error == ERR_INVALID_MAP)
		ft_putstr_fd(MSG_ERR_ERR_INVALID_MAP, STDERR_FILENO);
}

int	main(int ac, char **av)
{
	t_game	game;
	int		error;

	memset(&game, 0, sizeof(t_game));
	if (ac != 2 || !av[1] || !av[1][0])
		return (print_error(ERR_ARGS), 1);
	init_map_data(&game.map_data);
	error = map_parser(av[1], &game.map_data);
	if (error != SUCCESS)
		return (free_map_data(&game.map_data), print_error(error), 1);
	init_player_position(&game);

	if (game.map_data.ceiling_color)
	{
		game.ceiling_color_int = create_trgb(0, game.map_data.ceiling_color->r,
				game.map_data.ceiling_color->g, game.map_data.ceiling_color->b);
	}
	if (game.map_data.floor_color)
	{
		game.floor_color_int = create_trgb(0, game.map_data.floor_color->r,
				game.map_data.floor_color->g, game.map_data.floor_color->b);
	}

	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		return (1);
	game.win_ptr = mlx_new_window(game.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (game.win_ptr == NULL)
		return (1);

	// --- 더블 버퍼링을 위한 이미지 버퍼 생성 ---
	game.screen_buffer.img_ptr = mlx_new_image(game.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game.screen_buffer.img_ptr)
		return (perror("Screen buffer creation failed"), 1);
	game.screen_buffer.data = (int *)mlx_get_data_addr(game.screen_buffer.img_ptr,
		&game.screen_buffer.bpp, &game.screen_buffer.size_l, &game.screen_buffer.endian);
	// -----------------------------------------

	load_textures(&game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press_handler, &game);
	mlx_hook(game.win_ptr, 3, 1L << 1, key_release_handler, &game);
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);
	free_map_data(&game.map_data);
	return (0);
}