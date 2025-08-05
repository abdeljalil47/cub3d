#include "../header/cub3d.h"

int	check_left_move(t_table *table, float x, float y)
{
	int map_x = (int)(x / TILE_SIZE);
	int map_y = (int)((y + MOVE_FAKE) / TILE_SIZE);

	if (map_y < 0 || map_y >= table->height || map_x < 0 || map_x >= (int)ft_strlen(table->map_stru->dmaps[map_y]))
		return 1;

	if (table->map_stru->dmaps[map_y][map_x] == '1')
		return printf("\thave wall (left) at (%d, %d)\n", map_y, map_x), 1;

	return 0;
}

int	check_right_move(t_table *table, float x, float y)
{
	int map_x = (int)(x / TILE_SIZE);
	int map_y = (int)((y - MOVE_FAKE) / TILE_SIZE);

	if (map_y < 0 || map_y >= table->height || map_x < 0 || map_x >= (int)ft_strlen(table->map_stru->dmaps[map_y]))
		return 1;

	if (table->map_stru->dmaps[map_y][map_x] == '1')
		return printf("\thave wall (right) at (%d, %d)\n", map_y, map_x), 1;

	return 0;
}
