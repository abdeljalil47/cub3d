/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:09:01 by abdsebba          #+#    #+#             */
/*   Updated: 2025/09/03 14:41:32 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

void	put_pixel(t_table *table, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = table->img_data + (y * table->size_line + x * (table->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	put_pixel_minimap(t_table *table, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < table->minimap_size && y >= 0 && y < table->minimap_size)
	{
		dst = table->img_data + (y * table->size_line + x * (table->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_minimap_background(t_table *table)
{
	int	px;
	int	py;

	py = 0;
	while (py < table->minimap_size)
	{
		px = 0;
		while (px < table->minimap_size)
		{
			put_pixel_minimap(table, px, py, 0x607ea6);
			px++;
		}
		py++;
	}
}

void	clearwindow(t_table *table)
{
	int	px;
	int	py;

	py = 0;
	while (py < table->minimap_size)
	{
		px = 0;
		while (px < table->minimap_size)
		{
			put_pixel_minimap(table, px, py, 0x000000);
			px++;
		}
		py++;
	}
}

int	put_texture(t_table *table)
{
	int	i;
	int	y;

	clearwindow(table);
	render_3d_projection(table);
	draw_minimap_background(table);
	i = 0;
	while (table->map_stru->dmaps[i])
	{
		y = 0;
		while (table->map_stru->dmaps[i][y])
		{
			put_element(table, table->map_stru->dmaps[i][y], i, y);
			y++;
		}
		i++;
	}
	ft_put_player(&table);
	mlx_put_image_to_window(table->mlx, table->mlx_win, table->img, 0, 0);
	return (1);
}
