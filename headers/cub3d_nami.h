#include "../minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

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
int		init_all(t_game *game);
void	init_map_data(t_map_data *map_data);
void	init_color(t_game *game);