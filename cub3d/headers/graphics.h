/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelee <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:24:17 by jelee             #+#    #+#             */
/*   Updated: 2025/10/20 16:24:45 by jelee            ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "data.h"

void	init_ray_data(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	calculate_wall_projection(t_game *game, t_ray *ray);
void	draw_textured_line(t_game *game, t_ray *ray, int x);
void	load_textures(t_game *game);
int		create_trgb(int t, int r, int g, int b);
void	put_pixel_to_image(t_img *buffer, int x, int y, int color);
void	init_color(t_game *game);

#endif
