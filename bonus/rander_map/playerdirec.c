/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerdirec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:09:11 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/27 19:04:23 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

static int	get_step(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
}

static void	init_variable(int *dx, int *dy, int *sx, t_data *data)
{
	*dx = abs(data->x1 - data->x0);
	*dy = abs(data->y1 - data->y0);
	*sx = get_step(data->x0, data->x1);
}

void	draw_line(t_table *table, t_data *data, int e2, int err)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;

	init_variable(&dx, &dy, &sx, data);
	sy = get_step(data->y0, data->y1);
	err = dx - dy;
	while (1)
	{
		put_pixel_minimap(table, data->x0, data->y0, data->color);
		if (data->x0 == data->x1 && data->y0 == data->y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			data->x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			data->y0 += sy;
		}
	}
}

int	get_inverse_color(int color, char type)
{
	int	r;
	int	g;
	int	b;
	int	temp;

	r = 0;
	g = 0;
	b = 0;
	if (type == 'M')
	{
		r = 255 - ((color >> 16) & 0xFF);
		g = 255 - ((color >> 8) & 0xFF);
		b = 255 - (color & 0xFF);
	}
	else if (type == 'P')
	{
		temp = r;
		r = (b + 100) % 256;
		g = (g + 60) % 256;
		b = (temp + 30) % 256;
	}
	return ((r << 16) | (g << 8) | b);
}
