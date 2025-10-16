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
        x_line += x_inc;
        y_line += y_inc;
        i++;
    }
}
