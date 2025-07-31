#include "../header/cub3d.h"

/* === move the player===
	top->13
	bottom->1
	right->2
	left->0
	=========== change the player coordonne===
*/

int	ft_move_check(t_table *table, double x, double y)
{
	if (check_top_move(table, x, y)
		|| check_bottom_move(table, x, y)
		|| check_left_move(table, x, y)
		|| check_right_move(table, x, y))
		return 1;
	return 0;
}

void normalize_angle(double *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle > (2 * M_PI))
		*angle -= 2 * M_PI;
}

void check_player_fov(t_table *table, int *ray_leftright, int *ray_updown)
{
	printf("\033[0;32m-------->>%f\033[0m\n", fmod(table->player_coor->angle, 2 * M_PI));
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
	int map_inx = (x); // Map row
	int map_iny = (y); // Map column
	printf("\t\t%f %f\n", x, y);
	printf("\t\t%d %d\n", map_inx, map_iny);
	if (map_inx < 0 || map_inx > WINDOW_WIDTH || map_iny < 0 || map_iny > WINDOW_HEIGHT)
	{
		printf("Wall check: Out of bounds at (%d, %d)\n", map_inx, map_iny);
		return 1; // Out of bounds
	}
	printf("Wall check: Position (%d, %d) has value '%c'\n", map_inx, map_iny, table->map_stru->dmaps[map_inx][map_iny]);
	if (table->map_stru->dmaps[map_inx][map_iny] == '1')
		return 1; // Wall

	if (ft_move_check(table, x, y))
		return 1; // Wall

	return 0;
}

void player_coordonneup(t_table **data)
{
	t_table *table = *data;

	table->player_coor->angle += table->player_coor->rotate * ROTATION_SPEED;
	if (table->player_coor->angle < 0)
		table->player_coor->angle += 2 * M_PI;
	if (table->player_coor->angle >= 2 * M_PI)
		table->player_coor->angle -= 2 * M_PI;

	double new_x = table->player_coor->position_x;
	double new_y = table->player_coor->position_y;
	printf("..........>>%f\n", table->player_coor->angle);
	normalize_angle(&table->player_coor->angle);
	printf(".........>>%f\n", table->player_coor->angle);
	check_player_fov(table, &table->player_coor->player_fov, &table->player_coor->player_face);


	if (table->player_coor->forword_backword != 0)
	{
		double direction;
		if (table->player_coor->forword_backword > 0)
			direction = table->player_coor->angle;
		else
		{
			direction = table->player_coor->angle + M_PI;
		}

		new_x += sin(direction) * MOVE_SPEED;
		new_y += cos(direction) * MOVE_SPEED;
		printf("W or S pressed, direction: %f, new_x: %f, new_y: %f\n", direction, new_x, new_y);
	}

	if (table->player_coor->leftvu_rightvu != 0)
	{
		double strafe_angle;
		if (table->player_coor->leftvu_rightvu > 0)
			strafe_angle = table->player_coor->angle + (M_PI / 2);
		else
			strafe_angle = table->player_coor->angle + (-M_PI / 2);
		new_x += sin(strafe_angle) * MOVE_SPEED;
		new_y += cos(strafe_angle) * MOVE_SPEED;
		printf("A or D pressed, strafe_angle: %f, new_x: %f, new_y: %f\n", strafe_angle, new_x, new_y);
	}

	if (!has_wall_at(table, new_x, new_y))
	{
		table->player_coor->position_x = new_x;
		table->player_coor->position_y = new_y;
		printf("Position updated to (%f, %f)\n", new_x, new_y);
	}

	printf("\033[0;32m%d\033[0m\n", table->player_coor->player_face);
}
