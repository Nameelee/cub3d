#include "includes/cub3d.h"

void	draw_vertical_line(t_game *game, int x, int draw_start, int draw_end, int color)
{
	int	y;

	y = draw_start;
	while (y < draw_end)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
		y++;
	}
}

// Fonction pour fermer la fenêtre et quitter le programme proprement
int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	printf("Fenêtre fermée. Fin du programme.\n");
	exit(0);
	return (0);
}

int	game_loop(t_game *game)
{
	t_ray	ray;
	int		x;

	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		// 1. 현재 x 좌표에 대한 광선 데이터 초기화
		init_ray_data(game, &ray, x);

		// 2. DDA 알고리즘으로 벽 찾기
		perform_dda(game, &ray);

		// 3. 벽 높이 등 그리기 위한 정보 계산
		calculate_wall_projection(game, &ray);

		// 4. 색상을 정하고 실제 수직선 그리기 (13, 14번)
		int color;
		if (ray.side == 1)
			color = 0x00FF0000; // 빨간색
		else
			color = 0x0000FF00; // 초록색
		draw_vertical_line(game, x, ray.draw_start, ray.draw_end, color);
		
		x++;
	}
	return (0);
}

int	main(void)
{
	t_game	game;

	memset(&game, 0, sizeof(t_game));

	// 임시 맵 데이터 (벽 '1', 빈 공간 '0')
	char temp_map[MAP_WIDTH][MAP_HEIGHT] = {
		{'1','1','1','1','1','1','1','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','0','1','0','0','1','0','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','0','1','0','0','1','0','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','0','0','1','1','1','0','1'},
		{'1','1','1','1','1','1','1','1'}
	};
	// memcpy를 사용해 game.map으로 복사
	memcpy(game.map, temp_map, sizeof(temp_map));

	// 플레이어 초기 위치 및 방향 설정 (남쪽을 바라봄)
	game.player.pos_x = 4.5; // 맵의 중앙쯤
	game.player.pos_y = 4.5;
	game.player.dir_x = 1.0;  // 남쪽 방향
	game.player.dir_y = 0.0;
	game.player.plane_x = 0.0;
	game.player.plane_y = 0.66; // 66도의 시야각(FOV)

	// 1. Initialisation de la MiniLibX
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
	{
		perror("Échec de l'initialisation de la MiniLibX");
		return (1);
	}

	// 2. Création d'une nouvelle fenêtre
	game.win_ptr = mlx_new_window(game.mlx_ptr, 800, 600, "cub3D");
	if (game.win_ptr == NULL)
	{
		perror("Échec de la création de la fenêtre");
		return (1);
	}

	// 3. Enregistrement des gestionnaires d'événements
	// Appelle la fonction 'key_press_handler' lorsqu'une touche est pressée
	mlx_key_hook(game.win_ptr, key_press_handler, &game);
	// Appelle la fonction 'close_game' lorsque le bouton 'X' de la fenêtre est cliqué
	// L'événement 17 correspond au bouton de fermeture sur macOS ( "DestroyNotify" sur Linux)
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);

	// 4. Démarrage de la boucle d'événements
	// game_loop 함수를 계속해서 반복 실행하도록 등록
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);//continuer la boucle d'événements
	
	return (0);
}