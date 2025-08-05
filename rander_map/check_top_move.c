#include "../header/cub3d.h"

int	check_top_move(t_table *table, float x, float y)
{
	int map_x = (int)((x - MOVE_FAKE) / TILE_SIZE);
	int map_y = (int)(y / TILE_SIZE);
printf("\tcheck 1 (bottom) at (%d, %d)\n", map_y, map_x);

	if (map_x < 0 || map_y < 0 || map_y >= table->height ||
		map_x >= (int)ft_strlen(table->map_stru->dmaps[map_y]))
		return 1; // Out of bounds = treat as wall

	if (table->map_stru->dmaps[map_y][map_x] == '1')
	{
		printf("\thave wall (top) at (%d, %d)\n", map_y, map_x);
		return 1;
	}
	return 0;
}

int	check_bottom_move(t_table *table, float x, float y)
{
	int map_x = (int)((x + MOVE_FAKE) / TILE_SIZE);
	int map_y = (int)(y / TILE_SIZE);
printf("\tcheck 2 (bottom) at (%d, %d)\n", map_y, map_x);
	if (map_x < 0 || map_y < 0 || map_y >= table->height ||
		map_x >= (int)ft_strlen(table->map_stru->dmaps[map_y]))
		return 1; // Out of bounds = treat as wall

	if (table->map_stru->dmaps[map_y][map_x] == '1')
	{
		printf("\thave wall (bottom) at (%d, %d)\n", map_y, map_x);
		return 1;
	}
	return 0;
}

