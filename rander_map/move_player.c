#include "../header/cub3d.h"

/* === move the player===
	top->13
	bottom->1
	right->2
	left->0
*/

int	left_right(t_table *table, int key)
{
	int	prev_x;
	int	prev_y;

	prev_x = table->player_coor->position_x;
	prev_y = table->player_coor->position_y;
	if (key == 2)
	{
		if (table->map_stru->dmaps[prev_x][prev_y + 1] != '1') //right
		{
			table->player_coor->position_y += 1;
			mlx_clear_window(table->mlx, table->mlx_win);
			if (!put_texture(table))
				return 0;
		}
	}
	if (key == 0)
	{
		if (table->map_stru->dmaps[prev_x][prev_y - 1] != '1') //left
		{
			table->player_coor->position_y -= 1;
			mlx_clear_window(table->mlx, table->mlx_win);
			if (!put_texture(table))
				return 0;
		}
	}
	return 1;
}

int	move_player(t_table *table, int key)
{
	int	prev_x;
	int	prev_y;

	prev_x = table->player_coor->position_x;
	prev_y = table->player_coor->position_y;
	if (key == 13)
	{
		if (table->map_stru->dmaps[prev_x - 1][prev_y] != '1') //top
		{
			table->player_coor->position_x -= 1;
			mlx_clear_window(table->mlx, table->mlx_win);
			if (!put_texture(table))
				return 0;
		}
	}
	if (key == 1)
	{
		if (table->map_stru->dmaps[prev_x + 1][prev_y] != '1') //bottom
		{
			table->player_coor->position_x += 1;
			mlx_clear_window(table->mlx, table->mlx_win);
			if (!put_texture(table))
				return 0;
		}
	}
	else
		left_right(table, key);
	return 1;
}
