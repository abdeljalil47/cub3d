#include "../header/cub3d.h"


int	load_images(t_table *table)
{
	table->wall_img = mlx_xpm_file_to_image(table->mlx, table->map_ele->path, &table->width, &table->height);
	table->player = mlx_xpm_file_to_image(table->mlx, "texture/player.xpm", &table->width, &table->height);
	if (!table->wall_img || !table->player)
		return ft_putstr_fd("ERROR\nload images failed!\n", 2), 0;
	return 1;
}

int	put_element(t_table *table, char c, int x, int y)
{
	if (c == '1')
	{
		mlx_put_image_to_window(table->mlx, table->mlx_win, table->wall_img, x * 50, y * 50);
	}
	if (c == 'N')
		mlx_put_image_to_window(table->mlx, table->mlx_win, table->player, x * 50, y * 50);
	return 1;
}

int	put_texture(t_table *table)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (!load_images(table))
		return 0;
	while (table->map_stru->dmaps[i])
	{
		y = 0;
		while (table->map_stru->dmaps[i][y])
		{
			if (!put_element(table, table->map_stru->dmaps[i][y], i, y))
				return 0;
			y++;
		}
		i++;
	}
	return 1;
}
