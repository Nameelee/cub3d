/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* data.h                                             :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/09/09 00:30:46 by manuelma          #+#    #+#             */
/* Updated: 2025/09/11 18:49:37 by manuelma         ###   ########.fr       */
/* */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# define EXPECTED_PARAM_NBR 6

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_map_data
{
	t_color	*ceiling_color;
	t_color	*floor_color;
	char	*wall_n_t;
	char	*wall_s_t;
	char	*wall_w_t;
	char	*wall_e_t;
	char	**map;
}	t_map_data;

typedef struct s_img
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int     walk_direction;
	int     strafe_direction;
	int     turn_direction;
}	t_player;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img       textures[4];
	t_player	player;
	t_map_data	map_data;
}	t_game;

#endif