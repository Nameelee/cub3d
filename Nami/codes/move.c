#include "includes/cub3d.h"

// Fonction pour gérer les entrées clavier
int key_press_handler(int keycode, t_game *game)
{
	double move_speed = 0.2; // 이동 속도
	double rot_speed = 0.1;  // 회전 속도
	double padding = 0.7;//이거 안하면 캐릭터가 점으로 나옴. 미니맵은 부피감을 가지는데. 미니맵과 실제 게임에서의 불일치 해소를 위함 

	if (keycode == KEY_ESC)
		close_game(game);
	if (keycode == KEY_W) // 'W' 키: 앞으로 이동
	{
		// [수정] 맵 접근 인덱스를 [y][x] 순서로 변경
		if (game->map[(int)game->player.pos_y][(int)(game->player.pos_x + game->player.dir_x * (move_speed + padding))] == '0')
			game->player.pos_x += game->player.dir_x * move_speed;
		if (game->map[(int)(game->player.pos_y + game->player.dir_y * (move_speed + padding))][(int)game->player.pos_x] == '0')
			game->player.pos_y += game->player.dir_y * move_speed;
	}
	if (keycode == KEY_A)
	{
		// [수정] 맵 접근 인덱스를 [y][x] 순서로 변경
		if (game->map[(int)game->player.pos_y][(int)(game->player.pos_x - game->player.plane_x * (move_speed + padding))] == '0')
			game->player.pos_x -= game->player.plane_x * move_speed;
		if (game->map[(int)(game->player.pos_y - game->player.plane_y * (move_speed + padding))][(int)game->player.pos_x] == '0')
			game->player.pos_y -= game->player.plane_y * move_speed;
	}
	if (keycode == KEY_S)
	{
		// [수정] 맵 접근 인덱스를 [y][x] 순서로 변경
		if (game->map[(int)game->player.pos_y][(int)(game->player.pos_x - game->player.dir_x * (move_speed + padding))] == '0')
			game->player.pos_x -= game->player.dir_x * move_speed;
		if (game->map[(int)(game->player.pos_y - game->player.dir_y * (move_speed *padding))][(int)game->player.pos_x] == '0')
			game->player.pos_y -= game->player.dir_y * move_speed;
	}
	if (keycode == KEY_D)
	{
		// [수정] 맵 접근 인덱스를 [y][x] 순서로 변경
		if (game->map[(int)game->player.pos_y][(int)(game->player.pos_x + game->player.plane_x * (move_speed + padding))] == '0')
			game->player.pos_x += game->player.plane_x * move_speed;
		if (game->map[(int)(game->player.pos_y + game->player.plane_y * (move_speed + padding))][(int)game->player.pos_x] == '0')
			game->player.pos_y += game->player.plane_y * move_speed;
	}
	if (keycode == KEY_LEFT) // 오른쪽 화살표: 시야 회전
	{
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rot_speed) - game->player.dir_y * sin(-rot_speed);
		game->player.dir_y = old_dir_x * sin(-rot_speed) + game->player.dir_y * cos(-rot_speed);
		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rot_speed) - game->player.plane_y * sin(-rot_speed);
		game->player.plane_y = old_plane_x * sin(-rot_speed) + game->player.plane_y * cos(-rot_speed);
    	// 1. atan2 함수로 방향 벡터를 라디안(radian) 각도로 변환
    	//double angle_rad = atan2(game->player.dir_y, game->player.dir_x);
    	// 2. 라디안을 우리가 아는 각도(degree)로 변환 (M_PI는 원주율 π)
    	//double angle_deg = angle_rad * (180.0 / M_PI);

    	// 변환된 각도를 소수점 둘째 자리까지 출력
		/*
    	printf("X: %f, Y: %f, Angle: %.2f°\n", 
            game->player.pos_x, 
            game->player.pos_y,
            angle_deg);
		*/
	}
	if (keycode == KEY_RIGHT) // 왼쪽 화살표: 시야 회전
	{
		// 회전 방향을 결정하는 rot_speed의 부호가 반대입니다.
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rot_speed) - game->player.dir_y * sin(rot_speed);
		game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y * cos(rot_speed);
		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rot_speed) - game->player.plane_y * sin(rot_speed);
		game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y * cos(rot_speed);
        
		// --- 디버깅을 위한 printf 부분 (오른쪽 키와 동일) ---
		//double angle_rad = atan2(game->player.dir_y, game->player.dir_x);
		//double angle_deg = angle_rad * (180.0 / M_PI);
		/*
		printf("X: %f, Y: %f, Angle: %.2f°\n", 
			game->player.pos_x, 
			game->player.pos_y,
			angle_deg);
		*/
	}
	return (0);
}