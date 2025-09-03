#include "includes/cub3d.h"

// Fonction pour fermer la fenêtre et quitter le programme proprement
int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	printf("Fenêtre fermée. Fin du programme.\n");
	exit(0);
	return (0);
}

/*
int game_loop(t_game *game)
{
	// 1. 화면을 검은색으로 지운다 (나중에 바닥/천장 색으로 채움)
	// mlx_clear_window(game->mlx_ptr, game->win_ptr);

	// 2. 여기에 레이캐스팅 및 렌더링 코드가 들어갈 예정
	//    (지금은 비워둡니다)

	// (임시) 현재 플레이어 좌표 출력해서 움직임 확인하기
	printf("Player X: %f, Player Y: %f\n", game->player.pos_x, game->player.pos_y);

	return (0);
}
*/

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
	//mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);//continuer la boucle d'événements
	
	return (0);
}