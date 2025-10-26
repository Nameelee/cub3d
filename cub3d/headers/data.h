/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:05:37 by manuelma          #+#    #+#             */
/*   Updated: 2025/10/21 15:08:20 by manuelma         ###   ########.fr       */
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
# define MINIMAP_SCALE 15 //size of one tile
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
	int		*data;//the address of the memory of the image by mlx_get_data_addr
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
	double	camera_x;//The x-coordinate on the camera plane, ranging -1 ~ +1
	double	dir_x;//actual direction
	double	dir_y;
	int		map_x;//the ray start from here
	int		map_y;
	double	side_dist_x;//distance from the ray's start to the next X-side
	double	side_dist_y;
	double	delta_dist_x;//The distance the ray must travel to cross
	double	delta_dist_y;
	double	perp_wall_dist;//Perpendicular Wall Distance. This prevent fish eye
	int		step_x;//The direction to step in the map grid, either +1 or -1
	int		step_y;
	int		hit;//0: ray is traveling. 1:the ray has hit a wall
	int		side;//which sides wall hits. 0:X-side 1:Y-side
	int		line_height;//the height of pixel of the wall slice
	int		draw_start;//The vertical y pixel coordinates to draw the wall
	int		draw_end;
	int		tex_num;//the num of the texture you use
	double	wall_x;// the x location you hit (0.0 ~ 1.0)
	int		tex_x;// the x location of the texture
}	t_ray;

#endif