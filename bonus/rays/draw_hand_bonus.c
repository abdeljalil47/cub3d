/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hand_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:55:05 by ahbilla           #+#    #+#             */
/*   Updated: 2025/08/28 15:13:29 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

void	draw_scaled_hand(t_table *table, t_texture *hand, float scale_factor)
{
	int	y;
	int	x;
	int	tex_x;
	int	tex_y;
	int	color;

	table->scaled_width = (int)(hand->width * scale_factor);
	table->scaled_height = (int)(hand->height * scale_factor);
	table->start_x = WINDOW_WIDTH / 2 - table->scaled_width / 2;
	table->start_y = WINDOW_HEIGHT - table->scaled_height;
	y = 0;
	while (y < table->scaled_height)
	{
		x = 0;
		while (x < table->scaled_width)
		{
			tex_x = (int)(x / scale_factor);
			tex_y = (int)(y / scale_factor);
			color = get_texture_pixel(hand, tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0x000000)
				put_pixel(table, table->start_x + x, table->start_y + y, color);
			x++;
		}
		y++;
	}
}

static t_texture	*get_hand_texture(t_table *table, int *max_frames)
{
	if (table->handetype->flag)
	{
		*max_frames = HAND_FRAMES_KNIFE_MV;
		return (&table->handetype->hand_frames_mv
			[table->handetype->current_frame]);
	}
	*max_frames = HAND_FRAMES_KNIFE;
	return (&table->handetype->hand_frames[table->handetype->current_frame]);
}

static void	update_hand_animation(t_table *table, int max_frames)
{
	table->handetype->anim_counter++;
	if (table->handetype->anim_counter >= HAND_ANIM_SPEED)
	{
		table->handetype->current_frame++;
		if (table->handetype->current_frame >= max_frames)
		{
			table->handetype->current_frame = 0;
			if (table->handetype->flag)
				table->handetype->flag = false;
		}
		table->handetype->anim_counter = 0;
	}
}

void	draw_hand(t_table *table)
{
	t_texture	*hand;
	int			max_frames;
	float		scale_x;
	float		scale_y;
	float		scale_factor;

	scale_x = WINDOW_WIDTH / 1000.0f;
	scale_y = WINDOW_HEIGHT / 1200.0f;
	if (scale_x < scale_y)
		scale_factor = scale_x * 0.7f;
	else
		scale_factor = scale_y * 0.7f;
	hand = get_hand_texture(table, &max_frames);
	draw_scaled_hand(table, hand, scale_factor);
	if (table->handetype->flag
		&& table->handetype->current_frame == HAND_FRAMES_KNIFE_MV - 1)
	{
		table->handetype->flag = false;
		table->handetype->current_frame = 0;
		table->handetype->anim_counter = 0;
		return ;
	}
	update_hand_animation(table, max_frames);
}
