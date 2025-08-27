/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:32:58 by ahbilla           #+#    #+#             */
/*   Updated: 2025/08/27 16:27:39 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	validate_table(t_table *table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (i < 4)
	{
		if (!table->textures[i].img || !table->textures[i].data)
			return ;
		i++;
	}
}

float	calculate_wall_height(t_ray *ray
	, float player_angle, float dist_project)
{
	float	ray_angle;
	float	corrected_dist;
	float	wall_height;

	ray_angle = ray->ray_angle;
	corrected_dist = ray->distance * cos(ray_angle - player_angle);
	if (corrected_dist < 0.1f)
		corrected_dist = 0.1f;
	wall_height = (TILE_SIZE / corrected_dist) * dist_project;
	return (wall_height);
}

t_texture	*select_vertical_texture(t_ray *ray, t_table *table, int *flip_x)
{
	float		ray_angle;
	t_texture	*texture;

	ray_angle = ray->ray_angle;
	texture = NULL;
	if (ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2)
	{
		texture = &table->textures[2];
		*flip_x = 1;
	}
	else
	{
		texture = &table->textures[3];
		*flip_x = 0;
	}
	return (texture);
}

t_texture	*select_horizontal_texture(t_ray *ray, t_table *table, int *flip_x)
{
	float		ray_angle;
	t_texture	*texture;

	ray_angle = ray->ray_angle;
	texture = NULL;
	if (ray_angle > M_PI)
	{
		texture = &table->textures[1];
		*flip_x = 1;
	}
	else
	{
		texture = &table->textures[0];
		*flip_x = 0;
	}
	return (texture);
}

t_texture	*select_texture(t_ray *ray, t_table *table, int *flip_x)
{
	if (ray->was_hit_vertical)
		return (select_vertical_texture(ray, table, flip_x));
	else
		return (select_horizontal_texture(ray, table, flip_x));
}
