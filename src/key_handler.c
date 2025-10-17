/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelee <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:46:08 by jelee             #+#    #+#             */
/*   Updated: 2025/10/17 15:46:11 by jelee            ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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
