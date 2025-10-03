/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:14:38 by manuelma          #+#    #+#             */
/*   Updated: 2025/10/03 14:09:03 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

// XPM 파일을 로드하여 t_img 구조체에 저장하는 함수. 마뉴엘 코드에 맞춰서 변형되어 있다. 
void	load_textures(t_game *game)
{
	int		width;
	int		height;
	char	*paths[4]; // 텍스처 경로들을 담을 배열

	// game.map_data에 저장된 경로들을 배열로 정리합니다.
	paths[0] = game->map_data.wall_n_t; // 0: 북
	paths[1] = game->map_data.wall_s_t; // 1: 남
	paths[2] = game->map_data.wall_w_t; // 2: 서
	paths[3] = game->map_data.wall_e_t; // 3: 동

	for (int i = 0; i < 4; i++)
	{
		// mlx_xpm_file_to_image로 xpm 파일을 이미지로 변환
		game->textures[i].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
				paths[i], &width, &height);
		
		// 로딩 실패 시 에러 처리 (필수!)
		if (game->textures[i].img_ptr == NULL)
		{
			// TODO: 여기서 모든 리소스를 해제하고 게임을 종료하는
			// 에러 핸들링 함수를 호출해야 합니다.
			printf("Error: Texture '%s' loading failed.\n", paths[i]);
			exit(1); // 간단한 예시 종료
		}

		// 이미지 데이터 주소를 가져와 나중에 픽셀을 직접 다룰 수 있도록 저장
		game->textures[i].data = (int *)mlx_get_data_addr(
				game->textures[i].img_ptr, &game->textures[i].bpp,
				&game->textures[i].size_l, &game->textures[i].endian);
	}
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

void draw_tile(t_game *game, int x, int y, int color)
{
    int i;
    int j;
    
    i = 0;
    while (i < MINIMAP_SCALE)
    {
        j = 0;
        while (j < MINIMAP_SCALE)
        {
            mlx_pixel_put(game->mlx_ptr, game->win_ptr, x * MINIMAP_SCALE + j, y * MINIMAP_SCALE + i, color);
            j++;
        }
        i++;
    }
}

void draw_minimap(t_game *game)
{
    int y;
    int x;

    // 맵 타일 그리기
    y = 0;
    while (y < MAP_HEIGHT)
    {
        x = 0;
        while (x < MAP_WIDTH)
        {
            if (game->map_data.map[y][x] == '1')
                draw_tile(game, x, y, WALL_COLOR);
            else
                draw_tile(game, x, y, FLOOR_COLOR);
            x++;
        }
        y++;
    }

    // 플레이어 위치 그리기

    double precise_player_x;
    double precise_player_y;
    double start_draw_x;
    double start_draw_y;

    // 플레이어의 화면 좌표를 double로 계산하여 정밀도를 유지합니다.
    precise_player_x = game->player.pos_x * MINIMAP_SCALE;
    precise_player_y = game->player.pos_y * MINIMAP_SCALE;

    // 사각형이 그려질 시작점(top-left)을 double로 계산합니다.
    start_draw_x = precise_player_x - (PLAYER_SIZE / 2.0);
    start_draw_y = precise_player_y - (PLAYER_SIZE / 2.0);

    y = 0;
    while (y < PLAYER_SIZE)
    {
        x = 0;
        while (x < PLAYER_SIZE)
        {
            // 최종 픽셀 좌표를 계산하여 int로 변환 후 그립니다.
            mlx_pixel_put(game->mlx_ptr, game->win_ptr,
                (int)(start_draw_x + x),
                (int)(start_draw_y + y),
                PLAYER_COLOR);
            x++;
        }
        y++;
    }
	// --- 추가된 부분 ---
    // 플레이어가 바라보는 방향을 선으로 그립니다.
    int i;
    int line_length;
    double start_x;
    double start_y;
    double end_x;
    double end_y;

    // 선의 길이는 타일 크기 정도로 설정합니다.
    line_length = MINIMAP_SCALE; 
    
    // 선의 시작점 (플레이어의 중심)
    start_x = game->player.pos_x * MINIMAP_SCALE;
    start_y = game->player.pos_y * MINIMAP_SCALE;
    
    // 선의 끝점 (플레이어의 중심 + 방향벡터 * 길이)
    end_x = start_x + game->player.dir_x * line_length;
    end_y = start_y + game->player.dir_y * line_length;

    // 시작점부터 끝점까지 짧은 선을 그립니다.
    // 간단한 DDA(Digital Differential Analyzer) 알고리즘을 사용합니다.
    double dx = end_x - start_x;
    double dy = end_y - start_y;
    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    double x_inc = dx / steps;
    double y_inc = dy / steps;
    double x_line = start_x;
    double y_line = start_y;
    i = 0;
    while (i <= steps)
    {
        mlx_pixel_put(game->mlx_ptr, game->win_ptr, (int)x_line, (int)y_line, PLAYER_COLOR);
        x_line += x_inc;
        y_line += y_inc;
        i++;
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

		draw_textured_line(game, &ray, x);
		x++;
	}
	draw_minimap(game);
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
            if (game->map_data.map[y][x] == 'N' || game->map_data.map[y][x] == 'S' ||
                game->map_data.map[y][x] == 'W' || game->map_data.map[y][x] == 'E')
            {
                // 플레이어 위치 설정 (타일 중앙으로 보정하기 위해 +0.5)
                game->player.pos_x = x + 0.5;
                game->player.pos_y = y + 0.5;
                
                // 방향 설정
                set_player_direction(game, game->map_data.map[y][x]);
                
                // 맵에서 플레이어 위치를 빈 공간으로 변경
                game->map_data.map[y][x] = '0';
                return ; // 플레이어를 찾았으므로 함수 종료
            }
            x++;
        }
        y++;
    }
}
/*
int	main2(void)
{
	t_game	game;

	memset(&game, 0, sizeof(t_game));

	// 임시 맵 데이터 (벽 '1', 빈 공간 '0')
	char temp_map[MAP_HEIGHT][MAP_WIDTH] = {
		{'1','1','1','1','1','1','1','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','0','1','0','0','1','0','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','0','1','0','0','1','0','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','0','0','1','1','1','W','1'},
		{'1','1','1','1','1','1','1','1'}
	};
	// memcpy를 사용해 game.map으로 복사
	memcpy(game.map, temp_map, sizeof(temp_map));

	init_player_position(&game);
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
	{
		perror("Échec de l'initialisation de la MiniLibX");
		return (1);
	}
	game.win_ptr = mlx_new_window(game.mlx_ptr, 800, 600, "cub3D");
	if (game.win_ptr == NULL)
	{
		perror("Échec de la création de la fenêtre");
		return (1);
	}
	mlx_key_hook(game.win_ptr, key_press_handler, &game);
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);//continuer la boucle d'événements
	
	return (0);
}
*/

//=========Till here Nami's codes

void	init_map_data(t_map_data *map_data)
{
	map_data->ceiling_color = NULL;
	map_data->floor_color = NULL;
	map_data->wall_n_t = NULL;
	map_data->wall_s_t = NULL;
	map_data->wall_e_t = NULL;
	map_data->wall_w_t = NULL;
	map_data->map = NULL;
}

void	free_map_data(t_map_data *map_data)
{
	n_free((void **)&map_data->wall_n_t);
	n_free((void **)&map_data->wall_s_t);
	n_free((void **)&map_data->wall_e_t);
	n_free((void **)&map_data->wall_w_t);
	n_free((void **)&map_data->ceiling_color);
	n_free((void **)&map_data->floor_color);
	free_double((void ***)&map_data->map);
}

void	print_error(int error)
{
	if (error == ERR_ARGS)
		ft_putstr_fd(MSG_ERR_ARGS, STDERR_FILENO);
	else if (error == ERR_READ)
		ft_putstr_fd(MSG_ERR_READ, STDERR_FILENO);
	else if (error == ERR_FILE_NAME)
		ft_putstr_fd(MSG_ERR_FILE_NAME, STDERR_FILENO);
	else if (error == ERR_MISS_OR_INVAL_PARAM)
		ft_putstr_fd(MSG_ERR_MISS_OR_INVAL_PARAM, STDERR_FILENO);
	else if (error == ERR_MALLOC)
		ft_putstr_fd(MSG_ERR_MALLOC, STDERR_FILENO);
	else if (error == ERR_INVALID_MAP)
		ft_putstr_fd(MSG_ERR_ERR_INVALID_MAP, STDERR_FILENO);
}

int	main(int ac, char **av)
{
	t_game	game;//Nami
	memset(&game, 0, sizeof(t_game));
	int			error;

	if (ac != 2 || !av[1] || !av[1][0])
		return (print_error(ERR_ARGS), 1);
	init_map_data(&game.map_data);
	error = map_parser(av[1], &game.map_data);
	if (error != SUCCESS)
		return (free_map_data(&game.map_data), print_error(error), 1);
	// launch game
	init_player_position(&game);
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
	{
		perror("Échec de l'initialisation de la MiniLibX");
		return (1);
	}
	game.win_ptr = mlx_new_window(game.mlx_ptr, 800, 600, "cub3D");
	if (game.win_ptr == NULL)
	{
		perror("Échec de la création de la fenêtre");
		return (1);
	}
	load_textures(&game);
	mlx_key_hook(game.win_ptr, key_press_handler, &game);
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);//continuer la boucle d'événements
	free_map_data(&game.map_data);
	return (0);
}
