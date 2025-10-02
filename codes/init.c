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