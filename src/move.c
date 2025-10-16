#include "../headers/cub3d.h"
#include <math.h>

int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (keycode == KEY_W)
		game->player.walk_direction = 1;
	else if (keycode == KEY_S)
		game->player.walk_direction = -1;
	if (keycode == KEY_A)
		game->player.strafe_direction = -1;
	else if (keycode == KEY_D)
		game->player.strafe_direction = 1;
	if (keycode == KEY_LEFT)
		game->player.turn_direction = -1;
	else if (keycode == KEY_RIGHT)
		game->player.turn_direction = 1;
	return (0);
}

int	key_release_handler(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S)
		game->player.walk_direction = 0;
	if (keycode == KEY_A || keycode == KEY_D)
		game->player.strafe_direction = 0;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		game->player.turn_direction = 0;
	return (0);
}

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

void	move_player(t_game *game)
{
	double	move_speed;
	double	rot_speed;
	double	move_vec_x;
	double	move_vec_y;
	double	new_pos_x;
	double	new_pos_y;

	move_speed = 0.05;
	rot_speed = 0.03;
	if (game->player.turn_direction != 0)
	{
		double old_dir_x = game->player.dir_x;
		double old_plane_x = game->player.plane_x;
		double rs = rot_speed * game->player.turn_direction;
		game->player.dir_x = game->player.dir_x * cos(rs) - game->player.dir_y * sin(rs);
		game->player.dir_y = old_dir_x * sin(rs) + game->player.dir_y * cos(rs);
		game->player.plane_x = game->player.plane_x * cos(rs) - game->player.plane_y * sin(rs);
		game->player.plane_y = old_plane_x * sin(rs) + game->player.plane_y * cos(rs);
	}
	if (game->player.walk_direction != 0 || game->player.strafe_direction != 0)
	{
		move_vec_x = (game->player.dir_x * game->player.walk_direction)
			+ (game->player.plane_x * game->player.strafe_direction);
		move_vec_y = (game->player.dir_y * game->player.walk_direction)
			+ (game->player.plane_y * game->player.strafe_direction);
		new_pos_x = game->player.pos_x + move_vec_x * move_speed;
		new_pos_y = game->player.pos_y + move_vec_y * move_speed;
		new_pos_x = game->player.pos_x + move_vec_x * move_speed;
		new_pos_y = game->player.pos_y + move_vec_y * move_speed;
		if (new_pos_x >= 0 && (int)new_pos_x < game->map_data.width && game->map_data.map[(int)game->player.pos_y][(int)new_pos_x] == '0')
		{
			game->player.pos_x = new_pos_x;
		}
		if (new_pos_y >= 0 && (int)new_pos_y < game->map_data.height
			&& game->map_data.map[(int)new_pos_y][(int)game->player.pos_x] == '0')
		{
			game->player.pos_y = new_pos_y;
		}
	}
}