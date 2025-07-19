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

	table = (t_table *)param;
	printf("%d\n", key);
	exit(1);
	return 1;
}

int	rander_map(map_valid *map_element, map_cub *map_structure)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return 0;
	table->mlx = mlx_init();
	if (!table->mlx)
		return 0;//TODO: free_table()
	table->map_stru = map_structure;
	table->map_ele = map_element;
	table->player = map_structure->player_pos;

	table->width = count_height(table->map_stru->dmaps);
	table->height = ft_strlen(table->map_stru->dmaps[0]);

	table->mlx_win = mlx_new_window(table->mlx, table->width * 50, table->height * 50, "cub3d");
	if (!table->mlx_win)
		return 0;//TODO: free_table()
	if (!put_texture(table))
		return 0;//TODO: free_table()
	mlx_hook(table->mlx_win, 17, 0, keycode, table);
	mlx_key_hook(table->mlx_win, keycode , table);
	mlx_loop(table->mlx);
	return 1;//TODO: free_table()
}

