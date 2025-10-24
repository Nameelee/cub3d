/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelee <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:13:30 by jelee             #+#    #+#             */
/*   Updated: 2025/10/17 16:13:33 by jelee            ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/** 
 * ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1
 Convert pixel location(0~1024) into the location of camera(-1~+1)
 * ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
 with value of camera_x, it calcul the direction of the projection of the ray
 * ray->map_x = (int)game->player.pos_x;
 it set the starting point of projecting ray
 * ray->hit = 0;
 DDA algorithm works only ray->hit == 0
*/
static void	init_ray_vectors(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->hit = 0;
}

/**
if (ray->dir_x == 0) ray is vertical. 
	ray->delta_dist_x = 1e30; it gives very big number for its limit
	ray->delta_dist_x = fabs(1 / ray->dir_x); very big numeber
ray->dir_x < 0: when you move to left
	step_x = -1 means left
 */
static void	init_dda_x(t_game *game, t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x)
			* ray->delta_dist_x;
	}
}

static void	init_dda_y(t_game *game, t_ray *ray)
{
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y)
			* ray->delta_dist_y;
	}
}

void	init_ray_data(t_game *game, t_ray *ray, int x)
{
	init_ray_vectors(game, ray, x);
	init_dda_x(game, ray);
	init_dda_y(game, ray);
}
