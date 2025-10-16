#include "../minilibx/mlx.h"
#include <stdlib.h> // Requis pour la fonction exit()
#include <stdio.h>  // Requis pour la fonction perror()
#include <math.h>
#include <string.h> // Requis pour memcpy

// Le keycode pour la touche ESC sur macOS (65307 sur Linux)
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_W 119
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

#define MAP_WIDTH 8
#define MAP_HEIGHT 8

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define TEX_WIDTH 64
#define TEX_HEIGHT 64

//Minimap
#define MINIMAP_SCALE 15
#define PLAYER_SIZE 15
#define PLAYER_COLOR 0xFF0000
#define WALL_COLOR 0xFFFFFF
#define FLOOR_COLOR 0x808080

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

int		key_press_handler(int keycode, t_game *game);
int		key_release_handler(int keycode, t_game *game);
int		close_game(t_game *game);
void	init_ray_data(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	calculate_wall_projection(t_game *game, t_ray *ray);
int		game_loop(t_game *game);
void	draw_minimap(t_game *game);
void	free_map_data(t_map_data *map_data);
void	set_player_direction(t_game *game, char direction);
void	init_player_position(t_game *game);
void	put_pixel_to_image(t_img *buffer, int x, int y, int color);
void	init_color(t_game *game);
void	move_player(t_game *game);
void	draw_textured_line(t_game *game, t_ray *ray, int x);
void	load_textures(t_game *game);
int		create_trgb(int t, int r, int g, int b);