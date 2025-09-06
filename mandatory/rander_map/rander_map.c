/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:08:57 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/31 22:34:15 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

static t_table	*init_table(t_map_cub *map_structure,
					t_map_valid *map_element, t_player *player_cor)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->mlx = mlx_init();
	if (!table->mlx)
		return (free(table)
			, ft_putstr_fd("Function mlx_init() failed!\n", 2), NULL);
	table->map_stru = map_structure;
	table->map_ele = map_element;
	table->player_coor = player_cor;
	table->width = find_map_width(table->map_stru->dmaps);
	table->height = count_height(table->map_stru->dmaps);
	table->tex_path = malloc(sizeof(t_texture_path));
	if (!table->tex_path)
		return (free(table->mlx), free(table)
			, ft_putstr_fd("allocate texPath failed!\n", 2), NULL);
	return (table);
}

static int	init_image(t_table *table)
{
	table->img = mlx_new_image(table->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!table->img)
	{
		ft_putstr_fd("ERROR\nFailed to create image\n", 2);
		free(table->mlx);
		free(table->tex_path);
		free(table);
		return (0);
	}
	table->img_data = mlx_get_data_addr(table->img,
			&table->bpp, &table->size_line, &table->endian);
	if (!table->img_data)
	{
		mlx_destroy_image(table->mlx, table->img);
		ft_putstr_fd("ERROR\nFailed to get image data address\n", 2);
		free(table->mlx);
		free(table->tex_path);
		free(table);
		return (0);
	}
	return (1);
}

static int	init_window(t_table *table)
{
	table->mlx_win = mlx_new_window(table->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3D");
	if (!table->mlx_win)
	{
		mlx_destroy_image(table->mlx, table->img);
		ft_putstr_fd("ERROR\nFailed to create window\n", 2);
		free(table->mlx);
		free(table->tex_path);
		free(table);
		return (0);
	}
	return (1);
}

static int	init_projection(t_table *table)
{
	find_ceiling_floor(table, &table->ciel, &table->floor);
	if (table->ciel == -1 || table->floor == -1)
	{
		mlx_destroy_window(table->mlx, table->mlx_win);
		mlx_destroy_image(table->mlx, table->img);
		free(table->mlx);
		free(table->tex_path);
		free(table);
		return (
			ft_putstr_fd("ERROR\nFailed on texture part!!\n", 2), 0);
	}
	find_texture_wall_angle(table);
	if (load_textures(table))
	{
		mlx_destroy_window(table->mlx, table->mlx_win);
		mlx_destroy_image(table->mlx, table->img);
		free(table->mlx);
		free(table->tex_path);
		free(table);
		return (
			ft_putstr_fd("ERROR\nFailed on texture part!!\n", 2), 0);
	}
	return (1);
}

int	rander_map(t_map_valid **map_element, t_map_cub **map_structure,
		t_player **player_cor)
{
	t_table	*table;

	if (WINDOW_WIDTH == 0 || WINDOW_HEIGHT == 0)
	{
		print_window_error();
		ft_putstr_fd("\033[1;31mERROR: Window width or \
height cannot be 0!\n\033[0m",
			2);
		return (0);
	}
	table = init_table(*map_structure, *map_element, *player_cor);
	if (!table)
		return (0);
	if (!init_image(table))
		return (0);
	if (!init_window(table))
		return (0);
	if (!init_projection(table))
		return (0);
	mlx_hook(table->mlx_win, 2, 1L << 0, keycode, table);
	mlx_hook(table->mlx_win, 3, 1L << 1, relase_keycode, table);
	mlx_hook(table->mlx_win, 17, 0, close_window, table);
	mlx_loop_hook(table->mlx, mainloop, table);
	return (mlx_loop(table->mlx), 1);
}
