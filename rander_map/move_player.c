#include "../header/cub3d.h"

/* === move the player===
	top->13
	bottom->1
	right->2
	left->0
	=========== change the player coordonne===
*/

int ft_move_check(t_table *table, float x, float y)
{
	if (check_top_move(table, x, y) || check_bottom_move(table, x, y) || check_left_move(table, x, y) || check_right_move(table, x, y))
		return 1;
	return 0;
}

void normalize_angle(float *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle > (2 * M_PI))
		*angle -= 2 * M_PI;
}

void check_player_fov(t_table *table, int *ray_leftright, int *ray_updown)
{
	// printf("\033[0;32m-------->>%f\033[0m\n", fmod(table->player_coor->angle, 2 * M_PI));
	if (table->player_coor->angle > 0 && table->player_coor->angle < M_PI)
		*ray_updown = -1;
	else
		*ray_updown = 1;
	if (table->player_coor->angle < (0.5 * M_PI) || table->player_coor->angle > (1.5 * M_PI))
		*ray_leftright = -1;
	else
		*ray_leftright = 1;
}

int has_wall_at(t_table *table, float x, float y)
{
	int map_x = floor(x / TILE_SIZE);
	int map_y = floor(y / TILE_SIZE);

	if (map_x < 0 || map_y < 0)
		return 1;


	// printf("\t\tout bounds %d\n",  table->door_exist);
	if (table->map_stru->dmaps[map_y][map_x] == 'D' && table->open_door == 0)
		return 1;
	if (table->map_stru->dmaps[map_y][map_x] == 'D' && table->open_door == 1)
		return 0;
	if (map_x >= table->width || map_y >= table->height)
        return 1;
	if (table->map_stru->dmaps[map_y][map_x] == '1')
		return 1;



	if (ft_move_check(table, x, y))
		return 1;
	return 0;
}

void player_coordonneup(t_table **data)
{
	t_table *table = *data;
	// int map_w = table->width;  // in tiles
	// int map_h = table->height; // in tiles
	// float average_map_size = (map_w + map_h) / 2.0f;
	// float reference_map_size = 500.0f; // normal map size for your game

	// float MOVE_SPEED = (TILE_SIZE / 8.0f) * (average_map_size / reference_map_size);

	table->player_coor->angle += table->player_coor->rotate * ROTATION_SPEED;
	if (table->player_coor->angle < 0)
		table->player_coor->angle += 2 * M_PI;
	if (table->player_coor->angle >= 2 * M_PI)
		table->player_coor->angle -= 2 * M_PI;

	normalize_angle(&table->player_coor->angle);
	check_player_fov(table, &table->player_coor->player_fov, &table->player_coor->player_face);

	float move_step = table->player_coor->forword_backword * MOVE_SPEED;
	float strafe_step = table->player_coor->leftvu_rightvu * MOVE_SPEED;

	float new_x = table->player_coor->position_y * TILE_SIZE;
	float new_y = table->player_coor->position_x * TILE_SIZE;

	if (move_step != 0)
	{
		float move_angle = table->player_coor->angle;
		if (move_step < 0)
			move_angle += M_PI;
		new_x += cos(move_angle) * fabs(move_step);
		new_y += sin(move_angle) * fabs(move_step);
	}

	if (strafe_step != 0)
	{
		float strafe_angle = table->player_coor->angle + (strafe_step > 0 ? M_PI_2 : -M_PI_2);
		new_x += cos(strafe_angle) * fabs(strafe_step);
		new_y += sin(strafe_angle) * fabs(strafe_step);
	}
	if (!has_wall_at(table, new_x, new_y))
	{
		// printf("no wall front of the player\n");
		table->player_coor->position_y = new_x / TILE_SIZE;
		table->player_coor->position_x = new_y / TILE_SIZE;
	}
	// else if (returnstat == 2)
	// {
	// 	printf("door front of the player\n");
	// 	table->player_coor->position_y = (new_x / TILE_SIZE) - 0.5f;
	// 	table->player_coor->position_x = (new_y / TILE_SIZE) - 0.5f;
	// }
	// else
		return ;

	// if (table->open_door == 1 &&
    //     table->map_stru->dmaps[(int)table->player_coor->position_y][(int)table->player_coor->position_x] != 'D')
    // {
    //     table->open_door = 0;
	// 	table->map_stru->dmaps[(int)table->player_coor->position_y][(int)table->player_coor->position_x] = 'D';
	//     printf("Door closed!\n");
    // }

	// normalize_angle(&table->player_coor->angle);
	// float new_x = table->player_coor->position_x * TILE_SIZE;
	// float new_y = table->player_coor->position_y * TILE_SIZE;

	// if (table->player_coor->forword)
	// {
	// 	new_x += cos(table->player_coor->angle) * MOVE_SPEED;
	// 	new_y += sin(table->player_coor->angle) * MOVE_SPEED;
	// }

	// if (table->player_coor->backword)
	// {
	// 	new_x -= cos(table->player_coor->angle) * MOVE_SPEED;
	// 	new_y -= sin(table->player_coor->angle) * MOVE_SPEED;
	// }

	// if (table->player_coor->leftvu)
	// {
	// 	new_x += cos(table->player_coor->angle - M_PI / 2) * MOVE_SPEED;
	// 	new_y += sin(table->player_coor->angle - M_PI / 2) * MOVE_SPEED;
	// }

	// if (table->player_coor->rightvu)
	// {
	// 	new_x += cos(table->player_coor->angle + M_PI / 2) * MOVE_SPEED;
	// 	new_y += sin(table->player_coor->angle + M_PI / 2) * MOVE_SPEED;
	// }

	// if (table->player_coor->rotateleft)
	// {
	// 	table->player_coor->angle -= ROTATION_SPEED;
	// 	normalize_angle(&table->player_coor->angle);
	// }

	// if (table->player_coor->rotateright)
	// {
	// 	table->player_coor->angle += ROTATION_SPEED;
	// 	normalize_angle(&table->player_coor->angle);
	// }

	// if (!has_wall_at(table, new_x, new_y))
	// {
	// 	table->player_coor->position_x = new_x / TILE_SIZE;
	// 	table->player_coor->position_y = new_y / TILE_SIZE;
	// }
}
