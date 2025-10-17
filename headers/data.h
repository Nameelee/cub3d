/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 00:30:46 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/11 18:49:37 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# define EXPECTED_PARAM_NBR 6

# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define MAP_WIDTH 8
# define MAP_HEIGHT 8

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# define TEX_WIDTH 64
# define TEX_HEIGHT 64
//Minimap
# define MINIMAP_SCALE 15
# define PLAYER_SIZE 15
# define PLAYER_COLOR 0xFF0000
# define WALL_COLOR 0xFFFFFF
# define FLOOR_COLOR 0x808080


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
	int		width;
	int		height;
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
	int		walk_direction;
	int		strafe_direction;
	int		turn_direction;
}	t_player;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		textures[4];
	t_img		screen_buffer;
	t_player	player;
	t_map_data	map_data;
	int			ceiling_color_int;
	int			floor_color_int;
}	t_game;

typedef struct s_vector_set
{
	int		dir_x;
	int		dir_y;
	double	plane_x;
	double	plane_y;
}	t_vector_set;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;//the num of the texture you use
	double	wall_x;// the x location you hit (0.0 ~ 1.0)
	int		tex_x;// the x locatio of the texture
}	t_ray;

#endif