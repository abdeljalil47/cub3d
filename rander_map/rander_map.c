#include "../header/cub3d.h"

int	count_height(char **line)
{
	int i;

	i = 0;
	while (line[i])
	{
		i++;
	}
	return i;
}

int	keycode(int key, void *param)
{
	t_table	*table;

	/* === com of the player ===
	124->right
	123->left
	*/
	/* === move the player===
	top->13
	bottom->1
	right->2
	left->0
	*/
	table = (t_table *)param;
	printf("%d\n", key);
	if (key == 53 || key == 5696)
		exit(1);
	else if (!move_player(table, key))
		return 0;
	return 1;
}

int	rander_map(map_valid **map_element, map_cub **map_structure)
{
	t_table	*table;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return 0;
	table = malloc(sizeof(t_table));
	if (!table)
		return free(data), 0;
	table->mlx = mlx_init();
	if (!table->mlx)
		return 0;//TODO: free_table() free_data()
	table->map_stru = *map_structure;
	table->map_ele = *map_element;
	table->player_coor = (*map_structure)->player_pos;
	table->data = data;
	table->width = ft_strlen(table->map_stru->dmaps[0]);
	table->height = count_height(table->map_stru->dmaps);
	data->current_time = get_time();
	table->mlx_win = mlx_new_window(table->mlx, table->width * 50, table->height * 50, "cub3d");
	if (!table->mlx_win)
		return 0;//TODO: free_table() free_data()
	if (!put_texture(table))
		return 0;//TODO: free_table() free_data()
	mlx_hook(table->mlx_win, 17, 0, keycode, table);//close window
	mlx_key_hook(table->mlx_win, keycode , table);
	if (!get_path_frame(&table))
		return ft_putstr_fd("ERROR\ncreate frames failed!\n", 2), 0;
	mlx_loop_hook(table->mlx, player_effect, table);
	mlx_loop(table->mlx);
	return 1;//TODO: free_table() free_data()
}

