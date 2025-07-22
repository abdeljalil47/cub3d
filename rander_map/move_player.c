#include "../header/cub3d.h"

/* === move the player===
	top->13
	bottom->1
	right->2
	left->0
	=========== change the player coordonne===
*/
// int	has_wall_at(t_table *data, float x, float y)
// {
// 	if (x < 0 || x > data->data->width || y < 0 || y > data->height)
// 		return 1;
// 	int map_inx = (int)(x / (data->width / 2));
// 	int map_iny = (int)(y / (data->height / 2));
// 	return data->map_stru->dmaps[map_inx][map_iny] != 0;
// }

void	player_coordonneup(t_table **data)
{
	t_table *table = *data;

	printf("%d\n", table->player_coor->forword_backword);
	printf("%d\n", table->player_coor->leftword_rightword);

	table->player_coor->angle += table->player_coor->leftword_rightword * table->player_coor->rotation_speed;
	float movestep = table->player_coor->forword_backword * move_speed;
	float new_x = table->player_coor->position_y + cos(table->player_coor->angle) * movestep;
	float new_y = table->player_coor->position_x + sin(table->player_coor->angle) * movestep;

	table->player_coor->position_x = new_x;
	table->player_coor->position_y = new_y;

	put_texture(table);
}