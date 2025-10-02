#include "includes/cub3d.h"

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
            if (game->map[y][x] == '1')
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