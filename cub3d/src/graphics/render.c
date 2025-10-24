/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelee <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:17:51 by jelee             #+#    #+#             */
/*   Updated: 2025/10/17 16:17:53 by jelee            ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * the heart of DDA algorithm. it move the ray
 * while (ray->hit == 0): go on if ray didn't hit the wall
 * if (ray->side_dist_x < ray->side_dist_y)
 * : to next grid, which is smaller? distance_x or distance_y?
 * if distance_x is smaller then add the direction
 * so the ray decide its direction and move on
 */
static void	run_dda_loop(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map_data.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

/**
 * this function decide which wall the ray hit
side == 0 means the ray hit the wall x axis(E or W)
if (ray-> dir_x > 0) means E wall
 */
static void	set_wall_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			ray->tex_num = 3;
		else
			ray->tex_num = 2;
	}
	else
	{
		if (ray->dir_y > 0)
			ray->tex_num = 1;
		else
			ray->tex_num = 0;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	run_dda_loop(game, ray);
	set_wall_texture(ray);
}

/** 
 * perp_wall_dist: preventing fish eyes
 * for drawing, first draw vertical line.
 * ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	:it always draw wall in the center of the screen
if (ray->side == 0)
	ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	:when ray hit the vertical wall (W,E) it needs its y coordinate
	and save at ray->wall_x  
ray->wall_x -= floor(ray->wall_x);
	:if wall_X 5.7 then the value will be 0.7
	:this means the ray hit the 70% of wall tile
ray->tex_x = (int)(ray->wall_x * (double)TEX_WIDTH);
	:TEX_WIDTH is 60. 60 * 0.7 = 44.8 
	:to draw the wall bring the 44th vertical pixel
the last codes: it prevent the mirroring
*/
void	calculate_wall_projection(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end < 0)
		ray->draw_end = 0;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)TEX_WIDTH);
	if (ray->side == 0 && ray->dir_x < 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
}
