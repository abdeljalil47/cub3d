/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:41:37 by ahbilla           #+#    #+#             */
/*   Updated: 2025/08/28 15:15:07 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

void	calculate_texture_coords(t_ray *ray
	, t_texture *texture, int flip_x, int *tex_x)
{
	float	wall_hit;

	if (ray->was_hit_vertical)
		wall_hit = ray->wall_hit_y;
	else
		wall_hit = ray->wall_hit_x;
	*tex_x = (int)(wall_hit / TILE_SIZE * texture->width) % texture->width;
	if (flip_x)
		*tex_x = texture->width - *tex_x - 1;
	if (*tex_x < 0)
		*tex_x += texture->width;
}

static void	draw_ceiling_or_floor(t_table *table, t_render *r)
{
	if (r->y < r->top_pixel)
		put_pixel(table, r->x, r->y, table->ciel);
	else if (r->y > r->bottom_pixel)
		put_pixel(table, r->x, r->y, table->floor);
}

static void	draw_wall_pixel(t_table *table, t_texture *texture,
				t_render *r, int tex_x)
{
	int	tex_y;
	int	color;

	tex_y = (int)(r->tex_pos);
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	r->tex_pos += r->step;
	color = get_texture_pixel(texture, tex_x, tex_y);
	put_pixel(table, r->x, r->y, color);
}

void	render_wall_strip(t_table *table, t_texture *texture, int i, int tex_x)
{
	t_render	r;

	r.wall_height = calculate_wall_height(&table->rays[i],
			table->player_coor->angle,
			(WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2));
	get_pixel_bounds(r.wall_height, &r.top_pixel, &r.bottom_pixel);
	r.step = (float)texture->height / r.wall_height;
	r.tex_pos = (r.top_pixel - WINDOW_HEIGHT / 2 + r.wall_height / 2) * r.step;
	r.y = 0;
	while (r.y < WINDOW_HEIGHT)
	{
		r.x = i * WALL_STRIP_WIDTH;
		while (r.x < (i + 1) * WALL_STRIP_WIDTH)
		{
			if (r.y >= r.top_pixel && r.y <= r.bottom_pixel)
				draw_wall_pixel(table, texture, &r, tex_x);
			else
				draw_ceiling_or_floor(table, &r);
			r.x++;
		}
		r.y++;
	}
}

void	render_3d_projection(t_table *table)
{
	int			i;
	int			flip_x;
	int			tex_x;
	t_texture	*texture;

	validate_table(table);
	i = 0;
	while (i < NUM_RAYS)
	{
		flip_x = 0;
		texture = select_texture(&table->rays[i], table, &flip_x);
		if (!texture || !texture->data)
			return ;
		calculate_texture_coords(&table->rays[i], texture, flip_x, &tex_x);
		render_wall_strip(table, texture, i, tex_x);
		i++;
	}
	draw_hand(table);
}
