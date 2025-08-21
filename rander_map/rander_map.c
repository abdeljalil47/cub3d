#include "../header/cub3d.h"

int count_height(char **line)
{
	int i = 0;
	while (line[i])
	{
		i++;
	}
	return (i);
}

int keycode(int key, void *param)
{
	t_table *table;

	table = (t_table *)param;
	if (!table)
		return (0);
	if (key == 14)
    {
        weapon(table, "KNIFE_MV");
        table->hand_anim.flag = true;
        table->hand_anim.current_frame = 0;
        table->hand_anim.anim_counter = 0;
    }
	if (key == 259 || key == 260)
	{
		table->player_coor->forword_backword = 0;
		table->player_coor->leftvu_rightvu = 0;
		table->player_coor->rotate = 0;
		return (0);
	}
	if (key == 53)
		exit(1);
	if (key == 1)
		table->player_coor->forword_backword = -1;
	else if (key == 13)
		table->player_coor->forword_backword = 1;
	else if (key == 2)
		table->player_coor->leftvu_rightvu = 1;
	else if (key == 0)
		table->player_coor->leftvu_rightvu = -1;
	else if (key == 123)
		table->player_coor->rotate = -1;
	else if (key == 124)
		table->player_coor->rotate = 1;
	else if (key == 49)
	{
		// if (table->player_coor->leftvu_rightvu == 0 && table->player_coor->rotate == 0
				// && table->player_coor->forword_backword != -1)
			open_door(table);
	}
	return (0);
}

int relase_keycode(int keycode, t_table *data)
{
	player *player_data = data->player_coor;
	if (keycode == 259 || keycode == 260)
	{
		player_data->forword_backword = 0;
		player_data->leftvu_rightvu = 0;
		player_data->rotate = 0;
		// data->open_door = 0;
		return (0);
	}
	if (keycode == 13 || keycode == 1)
	{
		player_data->forword_backword = 0;
		// data->open_door = 0;
	}
	if (keycode == 0 || keycode == 2)
	{
		player_data->leftvu_rightvu = 0;
		// data->open_door = 0;
	}
	if (keycode == 123 || keycode == 124)
	{
		player_data->rotate = 0;
		// data->open_door = 0;
	}
	return 0;
}

int close_window(void *param)
{
	(void)param;
	// t_table *table = (t_table *)param;
	exit(0);
	return 0;
}

void cast_all_rays(t_table *table)
{
	float ray_angle = table->player_coor->angle - (FOV_ANGLE / 2);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		if (!cast_rays(table, ray_angle, i))
			exit(0);
		ray_angle += FOV_ANGLE / NUM_RAYS;
	}
}

int mainloop(void *param)
{
	t_table *table;

	table = (t_table *)param;
	player_coordonneup(&table);
	// check_close_door(table);
	ft_put_player(&table);
	cast_all_rays(table);
	put_texture(table);
	return (0);
}
void inetialise_mv(t_table *table)
{
    table->hand_anim.current_frame = 0;
    table->hand_anim.anim_counter = 0;
    table->hand_anim.flag = false;
}
int mouse_move(int x, int y, t_table *table)
{
    static int last_x = -1;
    double sensitivity = 0.004;
    if (last_x == -1)
        last_x = x;

    int delta_x = x - last_x;
    table->player_coor->angle += delta_x * sensitivity;

    last_x = x;
    (void)y; 
    return (0);
}
int rander_map(map_valid **map_element, map_cub **map_structure, player **player_cor)
{
	t_table *table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (0);
	table->mlx = mlx_init();
	if (!table->mlx)
		return (ft_putstr_fd("Function mlx_inti() failed!\n", 2), 0);
	table->open_door = 0;
	table->map_stru = *map_structure;
	table->map_ele = *map_element;
	table->player_coor = *player_cor;
	table->width = find_map_width(table->map_stru->dmaps);
	table->height = count_height(table->map_stru->dmaps);
	table->img = mlx_new_image(table->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!table->img)
		return (ft_putstr_fd("Error: Failed to create image\n", 2), 0);
	table->img_data = mlx_get_data_addr(table->img, &table->bpp, &table->size_line, &table->endian);
	if (!table->img_data)
		return (ft_putstr_fd("Error: Failed to get image data address\n", 2), mlx_destroy_image(table->mlx, table->img), 0);
	table->mlx_win = mlx_new_window(table->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!table->mlx_win)
		return (ft_putstr_fd("Error: Failed to create window\n", 2), mlx_destroy_image(table->mlx, table->img), 0);
    inetialise_mv(table);
    weapon(table, "KNIFE_MV");
    weapon(table, "KNIFE");

    mlx_hook(table->mlx_win, 2, 1L << 0, keycode, table);
    mlx_hook(table->mlx_win, 6, 1L<<6, mouse_move, table);
    mlx_hook(table->mlx_win, 3, 1L << 1, relase_keycode, table);
    mlx_hook(table->mlx_win, 17, 0, close_window, table);
    mlx_loop_hook(table->mlx, mainloop, table);
	mlx_loop(table->mlx);
	return (1);
}
