#include "../header/cub3d.h"

int	check_top_move(t_table *table, double x, double y)
{
	int		fake_x;
	int		fake_y;

	int m = (int)x;
	fake_x = (x) - (m == 1 ? 0 : MOVE_FAKE);
	fake_y = y;
	// printf("\thave 1 wall in this %d, %d\n", fake_x, fake_y);
	if (table->map_stru->dmaps[fake_x][fake_y] == '1')
		return printf("\thave 1 wall in this %d, %d, %c\n", fake_x, fake_y, table->map_stru->dmaps[fake_x][fake_y]), 1;
	return 0;
}

int	check_bottom_move(t_table *table, double x, double y)
{
	int		fake_x;
	int		fake_y;

	fake_x = (x + MOVE_FAKE);
	fake_y = y;
	if (table->map_stru->dmaps[fake_x][fake_y] == '1')
		return printf("\thave 2 wall in this %d, %d, %c\n", fake_x, fake_y, table->map_stru->dmaps[fake_x][fake_y]), 1;
	return 0;
}
