#include "includes/cub3d.h"

// 광선과 DDA 알고리즘에 필요한 변수들을 초기화하는 함수
void	init_ray_data(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y;
	}
}

// DDA 알고리즘을 실행하여 광선이 벽에 부딪힐 때까지 진행시키는 함수
void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
	}
    	// 어느 벽에 부딪혔는지 결정
	if (ray->side == 0) // x축 방향 벽 (동쪽 또는 서쪽)
	{
		if (ray->dir_x > 0)
			ray->tex_num = 3; // 동쪽
		else
			ray->tex_num = 2; // 서쪽
	}
	else // y축 방향 벽 (남쪽 또는 북쪽)
	{
		if (ray->dir_y > 0)
			ray->tex_num = 1; // 남쪽
		else
			ray->tex_num = 0; // 북쪽
	}
}

// 벽까지의 거리를 계산하고, 화면에 그릴 벽의 높이와 위치를 계산하는 함수
void	calculate_wall_projection(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;

    // 여기부터 텍스쳐 관련 코드
    // 벽에 부딪힌 정확한 x 좌표(wall_x)를 계산합니다.
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);

	// 텍스처의 x 좌표(tex_x)를 계산합니다.
	ray->tex_x = (int)(ray->wall_x * (double)TEX_WIDTH);
	if(ray->side == 0 && ray->dir_x < 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	if(ray->side == 1 && ray->dir_y > 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
}
