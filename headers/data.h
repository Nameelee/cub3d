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

// color stored in rgb from 0 to 255 (256 -> uchar)
typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

/**
 * @brief all of the map data
 * @param ceiling_color the color of the ceiling stored in rgb 0-255
 * @param floor_color the color of the floor stored in rgb 0-255
 * @param wall_n_t north facing wall texture path
 * @param wall_s_t south facing wall texture path
 * @param wall_w_t west facing wall texture path
 * @param wall_e_t east facing wall texture path
 * @param map list of strings with the actual map
 */
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
	int		*data; // 이미지의 픽셀 데이터 주소
	int		size_l;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	pos_x;     // 플레이어의 x 좌표
	double	pos_y;     // 플레이어의 y 좌표
	double	dir_x;     // 방향 벡터 x (-1 to 1)
	double	dir_y;     // 방향 벡터 y (-1 to 1)
	double	plane_x;   // 카메라 평면 벡터 x (시야각 결정)
	double	plane_y;   // 카메라 평면 벡터 y (시야각 결정)
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