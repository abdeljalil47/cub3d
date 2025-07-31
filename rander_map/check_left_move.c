#include "../header/cub3d.h"

int	check_left_move(t_table *table, double x, double y)
{
	int	fake_x;
	int	fake_y;

	fake_y = (y + MOVE_FAKE);
	fake_x = x;
	if (table->map_stru->dmaps[fake_x][fake_y] == '1')
		return printf("\thave 4 wall in this %d, %d, %c\n", fake_x, fake_y, table->map_stru->dmaps[fake_x][fake_y]), 1;
	return 0;
}

int	check_right_move(t_table *table, double x, double y)
{
	int	fake_x;
	int	fake_y;

	fake_y = (y - MOVE_FAKE);
	fake_x = x;
	if (table->map_stru->dmaps[fake_x][fake_y] == '1')
		return printf("\thave 4 wall in this %d, %d, %c\n", fake_x, fake_y, table->map_stru->dmaps[fake_x][fake_y]), 1;
	return 0;
}
