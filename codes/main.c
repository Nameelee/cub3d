#include "includes/cub3d.h"

// XPM 파일을 로드하여 t_img 구조체에 저장하는 함수
void	load_texture(t_game *game, int tex_num, char *path, int w, int h)
{
	game->textures[tex_num].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &w, &h);
	if (!game->textures[tex_num].img_ptr)
	{
		perror("Error: Failed to load texture");
		exit(EXIT_FAILURE);
	}
	game->textures[tex_num].data = (int *)mlx_get_data_addr(
		game->textures[tex_num].img_ptr,
		&game->textures[tex_num].bpp,
		&game->textures[tex_num].size_l,
		&game->textures[tex_num].endian
	);
}

// 텍스처를 입힌 수직선을 그리는 함수
//******코드가 좀 이상함 다듬어야 할 듯 *************/
void	draw_textured_line(t_game *game, t_ray *ray, int x)
{
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;

	//천정 그리기
	y = 0;
	while (y < ray->draw_start)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, 0x808080);
		y++;
	}
	//바닥 그리기
	y = ray->draw_end; // y를 벽 그리기가 끝난 지점부터 시작
	while (y < SCREEN_HEIGHT)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, 0x0000FF);
		y++;
	}

	// 텍스처의 y 좌표를 얼마나 증가시킬지 계산
	step = 1.0 * TEX_HEIGHT / ray->line_height;
	// 그리기 시작 지점의 텍스처 y 좌표 계산
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
	
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		// 텍스처의 y 좌표를 정수로 변환
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		
		// tex_x, tex_y를 이용해 텍스처에서 해당 픽셀의 색상 값을 가져옴
		color = game->textures[ray->tex_num].data[TEX_HEIGHT * tex_y + ray->tex_x];

        // y축 벽(남/북)은 약간 어둡게 표현하여 입체감을 줍니다.
        if (ray->side == 1)
            color = (color >> 1) & 8355711; // 비트 연산으로 밝기를 절반으로 줄임
		
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
		y++;
	}
}

//draw_textured_line 함수가 나오면서 요 함수는 안 쓰이게 됨
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

		/* 4. 색상을 정하고 실제 수직선 그리기 (13, 14번) draw_textured_line 함수로 대체
		int color;
		if (ray.side == 1)
			color = 0x00FF0000; // 빨간색
		else
			color = 0x0000FF00; // 초록색
		draw_vertical_line(game, x, ray.draw_start, ray.draw_end, color);
		*/
		draw_textured_line(game, &ray, x);
		x++;
	}
	return (0);
}

void set_player_direction(t_game *game, char direction)
{
    if (direction == 'N')
    {
        game->player.dir_x = 0;
        game->player.dir_y = -1;
        game->player.plane_x = 0.66;//시야각이라는데? (FOV)
        game->player.plane_y = 0;
    }
    else if (direction == 'S')
    {
        game->player.dir_x = 0;
        game->player.dir_y = 1;
        game->player.plane_x = -0.66;
        game->player.plane_y = 0;
    }
    else if (direction == 'W')
    {
        game->player.dir_x = -1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = -0.66;
    }
    else if (direction == 'E')
    {
        game->player.dir_x = 1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = 0.66;
    }
}

void init_player_position(t_game *game)
{
    int y;
    int x;

    y = 0;
    while (y < MAP_HEIGHT)
    {
        x = 0;
        while (x < MAP_WIDTH)
        {
            if (game->map[y][x] == 'N' || game->map[y][x] == 'S' ||
                game->map[y][x] == 'W' || game->map[y][x] == 'E')
            {
                // 플레이어 위치 설정 (타일 중앙으로 보정하기 위해 +0.5)
                game->player.pos_x = x + 0.5;
                game->player.pos_y = y + 0.5;
                
                // 방향 설정
                set_player_direction(game, game->map[y][x]);
                
                // 맵에서 플레이어 위치를 빈 공간으로 변경
                game->map[y][x] = '0';
                return ; // 플레이어를 찾았으므로 함수 종료
            }
            x++;
        }
        y++;
    }
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
		{'1','0','1','0','W','1','0','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','0','0','1','1','1','0','1'},
		{'1','1','1','1','1','1','1','1'}
	};
	// memcpy를 사용해 game.map으로 복사
	memcpy(game.map, temp_map, sizeof(temp_map));

	// 플레이어 초기 위치 및 방향 설정 (남쪽을 바라봄)
	//game.player.pos_x = 4.5; // 맵의 중앙쯤
	//game.player.pos_y = 4.5;
	//game.player.dir_x = 1.0;  // 남쪽 방향
	//game.player.dir_y = 0.0;
	//game.player.plane_x = 0.0;
	//game.player.plane_y = 0.66; // 66도의 시야각(FOV)
	init_player_position(&game);
	// 1. Initialisation de la MiniLibX
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
	{
		perror("Échec de l'initialisation de la MiniLibX");
		return (1);
	}

	// 텍스처 로드 (경로는 실제 파일 위치에 맞게 수정해야 합니다)
	// 예: 프로젝트 루트에 textures 폴더를 만들고 그 안에 xpm 파일들을 넣으세요.
	load_texture(&game, 0, "./textures/greek1.xpm", TEX_WIDTH, TEX_HEIGHT);
	load_texture(&game, 1, "./textures/greek2.xpm", TEX_WIDTH, TEX_HEIGHT);
	load_texture(&game, 2, "./textures/greek3.xpm", TEX_WIDTH, TEX_HEIGHT);
	load_texture(&game, 3, "./textures/greek4.xpm", TEX_WIDTH, TEX_HEIGHT);

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