#include <mlx.h>
#include <stdlib.h> // Requis pour la fonction exit()
#include <stdio.h>  // Requis pour la fonction perror()
#include <math.h>
#include <string.h> // Requis pour memcpy

// Le keycode pour la touche ESC sur macOS (65307 sur Linux)
#define KEY_ESC 53
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_LEFT 123
#define KEY_RIGHT 124

#define MAP_WIDTH 8
#define MAP_HEIGHT 8

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct s_player
{
	double	pos_x;     // 플레이어의 x 좌표
	double	pos_y;     // 플레이어의 y 좌표
	double	dir_x;     // 방향 벡터 x (-1 to 1)
	double	dir_y;     // 방향 벡터 y (-1 to 1)
	double	plane_x;   // 카메라 평면 벡터 x (시야각 결정)
	double	plane_y;   // 카메라 평면 벡터 y (시야각 결정)
}	t_player;

// Structure pour regrouper les variables relatives à la MLX
typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		map[MAP_WIDTH][MAP_HEIGHT]; // 2D 맵 데이터
	t_player	player;                     // 플레이어 데이터
}	t_game;

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
}	t_ray;

int		key_press_handler(int keycode, t_game *game);
int		close_game(t_game *game);
void	init_ray_data(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	calculate_wall_projection(t_game *game, t_ray *ray);
int		game_loop(t_game *game);