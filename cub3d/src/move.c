/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelee <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:46:27 by jelee             #+#    #+#             */
/*   Updated: 2025/10/17 15:46:30 by jelee            ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * dir_x: 1(to right) ~ -1(to left) / 0(not moving)
 * dir_y: 1(to north) ~ -1(to south)
 * plane_x: filed of view(the angle). 
 when it getting biger, you can see more thing and smaller. 
 */
void	set_player_vectors(t_game *game, t_vector_set vectors)
{
	game->player.dir_x = vectors.dir_x;
	game->player.dir_y = vectors.dir_y;
	game->player.plane_x = vectors.plane_x;
	game->player.plane_y = vectors.plane_y;
}

void	set_player_direction(t_game *game, char direction)
{
	if (direction == 'N')
		set_player_vectors(game, (t_vector_set){0, -1, 0.66, 0});
	else if (direction == 'S')
		set_player_vectors(game, (t_vector_set){0, 1, -0.66, 0});
	else if (direction == 'W')
		set_player_vectors(game, (t_vector_set){-1, 0, 0, -0.66});
	else if (direction == 'E')
		set_player_vectors(game, (t_vector_set){1, 0, 0, 0.66});
}

/**
 * rotation matrix: when you rotate in the angle of rs
x′=x⋅cos(rs)−y⋅sin(rs)
y′=x⋅sin(rs)+y⋅cos(rs)
 */
static	void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rs;

	if (game->player.turn_direction == 0)
		return ;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	rs = rot_speed * game->player.turn_direction;
	game->player.dir_x = game->player.dir_x
		* cos(rs) - game->player.dir_y * sin(rs);
	game->player.dir_y = old_dir_x * sin(rs) + game->player.dir_y * cos(rs);
	game->player.plane_x = game->player.plane_x
		* cos(rs) - game->player.plane_y * sin(rs);
	game->player.plane_y = old_plane_x * sin(rs) + game->player.plane_y
		* cos(rs);
}

/**
 * last two if's are collision check. 
 * this code makes player slide when it collides wall and pushed. 
 */
static	void	perform_movement(t_game *game, double move_speed)
{
	double	move_vec_x;
	double	move_vec_y;
	double	new_pos_x;
	double	new_pos_y;

	if (game->player.walk_direction == 0 && game->player.strafe_direction == 0)
		return ;
	move_vec_x = (game->player.dir_x * game->player.walk_direction)
		+ (game->player.plane_x * game->player.strafe_direction);
	move_vec_y = (game->player.dir_y * game->player.walk_direction)
		+ (game->player.plane_y * game->player.strafe_direction);
	new_pos_x = game->player.pos_x + move_vec_x * move_speed;
	new_pos_y = game->player.pos_y + move_vec_y * move_speed;
	if (game->map_data.map[(int)game->player.pos_y][(int)new_pos_x] == '0')
		game->player.pos_x = new_pos_x;
	if (game->map_data.map[(int)new_pos_y][(int)game->player.pos_x] == '0')
		game->player.pos_y = new_pos_y;
}

void	move_player(t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.03;
	rotate_player(game, rot_speed);
	perform_movement(game, move_speed);
}
