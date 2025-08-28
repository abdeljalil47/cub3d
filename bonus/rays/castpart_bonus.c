/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castpart_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:08:38 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:13:22 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

static void	init_horz_data(t_table *table, float ray_angle, t_horz_data *d)
{
	d->player_x = table->player_coor->position_y * TILE_SIZE;
	d->player_y = table->player_coor->position_x * TILE_SIZE;
	d->facing_up = (ray_angle > M_PI);
	d->next_y = floor(d->player_y / TILE_SIZE) * TILE_SIZE;
	if (!d->facing_up)
		d->next_y += TILE_SIZE;
	d->next_x = d->player_x + (d->next_y - d->player_y) / tan(ray_angle);
	if (d->facing_up)
		d->y_step = -TILE_SIZE;
	else
		d->y_step = TILE_SIZE;
	d->x_step = d->y_step / tan(ray_angle);
}

static float	check_horz_hits(t_table *table, t_horz_data *d,
		float *hit_x, float *hit_y)
{
	float	checky;

	while (d->next_x >= 0 && d->next_y >= 0
		&& d->next_x < table->width * TILE_SIZE
		&& d->next_y < table->height * TILE_SIZE)
	{
		if (d->facing_up)
			checky = d->next_y - 1;
		else
			checky = d->next_y;
		if (has_wall_at_for_ray(table, d->next_x, checky))
		{
			*hit_x = d->next_x;
			*hit_y = d->next_y;
			return (sqrtf(powf(d->player_x - *hit_x, 2)
					+ powf(d->player_y - *hit_y, 2)));
		}
		d->next_x += d->x_step;
		d->next_y += d->y_step;
	}
	return (1000000);
}

float	cast_horz_intersection(t_table *table,
		float ray_angle, float *hit_x, float *hit_y)
{
	t_horz_data	d;

	init_horz_data(table, ray_angle, &d);
	return (check_horz_hits(table, &d, hit_x, hit_y));
}

int	has_wall_at_for_ray(t_table *table, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(x / TILE_SIZE);
	map_y = (int)floor(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_y >= table->height
		|| map_x >= (int)ft_strlen(table->map_stru->dmaps[map_y]))
		return (1);
	if (!table->map_stru || !table->map_stru->dmaps)
		return (1);
	return (table->map_stru->dmaps[map_y][map_x] == '1');
}

int	find_map_width(char **dmaps)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	while (dmaps[i])
	{
		len = ft_strlen(dmaps[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}
