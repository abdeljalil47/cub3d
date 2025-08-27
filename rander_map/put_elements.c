/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:09:05 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/27 17:32:54 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

static void	draw_element_tile(t_table *table, int start_x
	, int start_y, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < (int)(TILE_SIZE * MINIMAP_SCALE))
	{
		dx = 0;
		while (dx < (int)(TILE_SIZE * MINIMAP_SCALE))
		{
			put_pixel_minimap(table, start_x + dx, start_y + dy, color);
			dx++;
		}
		dy++;
	}
}

void	init_lineplayer(t_table *table)
{
	int		end_x;
	int		end_y;
	int		color;
	t_data	data;

	color = get_inverse_color(table->ciel, 'P');
	end_x = table->minimap_center
		+ (int)(cos(table->player_coor->angle) * 18);
	end_y = table->minimap_center
		+ (int)(sin(table->player_coor->angle) * 18);
	data.color = color;
	data.x0 = table->minimap_center;
	data.x1 = end_x;
	data.y0 = table->minimap_center;
	data.y1 = end_y;
	draw_line(table, &data, 0, 0);
}

int	put_element(t_table *table, char c, int x, int y)
{
	int		color;
	int		start_x;
	int		start_y;
	float	player_px;
	float	player_py;

	if (c != '1')
		return (1);
	color = get_inverse_color(table->ciel, 'M');
	player_px = table->player_coor->position_y * TILE_SIZE;
	player_py = table->player_coor->position_x * TILE_SIZE;
	start_x = table->minimap_center + (y * TILE_SIZE - player_px)
		* MINIMAP_SCALE;
	start_y = table->minimap_center + (x * TILE_SIZE - player_py)
		* MINIMAP_SCALE;
	draw_element_tile(table, start_x, start_y, color);
	init_lineplayer(table);
	return (1);
}

static void	draw_player(int radius, t_table *table, int color)
{
	int	center_x;
	int	center_y;
	int	i;
	int	j;

	center_x = table->minimap_center;
	center_y = table->minimap_center;
	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if (i * i + j * j <= radius * radius)
				put_pixel_minimap(table, center_x + j, center_y + i, color);
			j++;
		}
		i++;
	}
}

int	ft_put_player(t_table **data)
{
	t_table	*table;
	int		color;
	int		radius;

	table = *data;
	color = get_inverse_color(table->ciel, 'P');
	radius = table->player_coor->radius;
	if (radius <= 0 || radius > 16)
		radius = 8;
	draw_player(radius, table, color);
	return (1);
}
