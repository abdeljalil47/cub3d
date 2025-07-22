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
	// int prev_x;
	// int prev_y;

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
	if (!table)
		return 0;
	// prev_x = table->player_coor->position_x;
	// prev_y = table->player_coor->position_y;
	if (key == 53 || key == 2944)
		exit(1);

	if (key == 13)
	{
		printf("pp1:%d\n", key);
		table->player_coor->forword_backword = 1;
	}
	else if (key == 1)
		table->player_coor->forword_backword = -1;
	else if (key == 123)
		table->player_coor->leftword_rightword = 1;
	else if (key == 124)
		table->player_coor->leftword_rightword = -1;
	// if (!move_player(table, key, prev_x, prev_y))
	// 	return 0;
	player_coordonneup(&table);
	return 0;
}

int	relase_keycode(int keycode, t_table *data)
{
	player *player_data = data->player_coor;
	if (keycode == 13 || keycode == 1)
		player_data->forword_backword = 0;
	else if (keycode == 0 || keycode == 2)
		player_data->leftword_rightword = 0;
	return 0;
}

int	close_window(void *param)
{
    t_table *table = (t_table *)param;
	(void)table;
    //TODO: free() all stuff
    exit(0);
    return 0;
}

int	rander_map(map_valid **map_element, map_cub **map_structure, player **player_cor)
{
	t_table	*table;
	t_data	*data2;

	data2 = malloc(sizeof(t_data));
	if (!data2)
		return 0;
	table = malloc(sizeof(t_table));
	if (!table)
		return free(data2), 0;
	table->mlx = mlx_init();
	if (!table->mlx)
		return 0;//TODO: free_table() free_data()

	table->map_stru = *map_structure;
	table->map_ele = *map_element;
	table->player_coor = *player_cor;
	table->data = data2;

	table->width = ft_strlen(table->map_stru->dmaps[0]);
	table->height = count_height(table->map_stru->dmaps);

	data2->current_time = get_time();
	data2->frame_id = 0;
	data2->img = NULL;

	table->mlx_win = mlx_new_window(table->mlx, table->width * 32, table->height * 32, "cub3d");
	if (!table->mlx_win)
		return 0;//TODO: free_table() free_data()
	if (!put_texture(table))
		return 0;//TODO: free_table() free_data()
	// if (!get_path_frame(&table))
	// 	return ft_putstr_fd("ERROR\ncreate frames failed!\n", 2), 0;
	// mlx_loop_hook(table->mlx, player_effect, table);
	// mlx_hook(table->mlx_win, 2, 1L<<0, keycode , table);
	mlx_hook(table->mlx_win, 2, 1L<<0, keycode , table);
	// mlx_hook(table->mlx_win, 3, 1L<<1, relase_keycode , table);
	mlx_hook(table->mlx_win, 17, 0, close_window, table);//close window

	mlx_loop(table->mlx);
	return 1;//TODO: free_table() free_data()
}

