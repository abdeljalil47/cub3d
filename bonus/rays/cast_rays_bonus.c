/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:08:44 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:13:14 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

static void	init_vert_data(t_table *table, float ray_angle, t_vert_data *d)
{
	d->player_x = table->player_coor->position_y * TILE_SIZE;
	d->player_y = table->player_coor->position_x * TILE_SIZE;
	d->facing_left = (ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2);
	d->next_x = floor(d->player_x / TILE_SIZE) * TILE_SIZE;
	if (!d->facing_left)
		d->next_x += TILE_SIZE;
	d->next_y = d->player_y + (d->next_x - d->player_x) * tan(ray_angle);
	if (d->facing_left)
		d->x_step = -TILE_SIZE;
	else
		d->x_step = TILE_SIZE;
	d->y_step = d->x_step * tan(ray_angle);
}

static float	check_vert_hits(t_table *table, t_vert_data *d,
		float *hit_x, float *hit_y)
{
	float	checkx;

	while (d->next_x >= 0 && d->next_y >= 0
		&& d->next_x < table->width * TILE_SIZE
		&& d->next_y < table->height * TILE_SIZE)
	{
		if (d->facing_left)
			checkx = d->next_x - 1;
		else
			checkx = d->next_x;
		if (has_wall_at_for_ray(table, checkx, d->next_y))
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

static float	cast_vert_intersection(t_table *table,
		float ray_angle, float *hit_x, float *hit_y)
{
	t_vert_data	d;

	init_vert_data(table, ray_angle, &d);
	return (check_vert_hits(table, &d, hit_x, hit_y));
}

static void	store_hit(t_ray *ray, float x, float y,
		int vertical)
{
	ray->wall_hit_x = x;
	ray->wall_hit_y = y;
	ray->was_hit_vertical = vertical;
}

int	cast_rays(t_table *table, float ray_angle, int columnid)
{
	t_hit	horz;
	t_hit	vert;
	t_ray	*ray;

	normalize_angle(&ray_angle);
	horz.dist = cast_horz_intersection(table, ray_angle, &horz.x, &horz.y);
	vert.dist = cast_vert_intersection(table, ray_angle, &vert.x, &vert.y);
	ray = &table->rays[columnid];
	if (horz.dist < vert.dist)
	{
		store_hit(ray, horz.x, horz.y, 0);
		ray->distance = horz.dist;
	}
	else
	{
		store_hit(ray, vert.x, vert.y, 1);
		ray->distance = vert.dist;
	}
	ray->ray_angle = ray_angle;
	return (1);
}
