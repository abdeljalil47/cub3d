/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:09:15 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/30 22:43:03 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	normalize_angle(float *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle > (2 * M_PI))
		*angle -= 2 * M_PI;
}

static void	update_angle(t_player *p)
{
	p->angle += p->rotate * ROTATION_SPEED;
	if (p->angle < 0)
		p->angle += 2 * M_PI;
	if (p->angle >= 2 * M_PI)
		p->angle -= 2 * M_PI;
	normalize_angle(&p->angle);
}

static void	apply_movement(t_table *table, float *new_x, float *new_y)
{
	float	move_step;
	float	move_angle;

	move_step = table->player_coor->forword_backword * MOVE_SPEED;
	if (move_step == 0)
		return ;
	move_angle = table->player_coor->angle;
	if (move_step < 0)
		move_angle += M_PI;
	*new_x += cos(move_angle) * fabs(move_step);
	*new_y += sin(move_angle) * fabs(move_step);
}

static void	apply_strafe(t_table *table, float *new_x, float *new_y)
{
	float	strafe_step;
	float	strafe_angle;

	strafe_step = table->player_coor->leftvu_rightvu * MOVE_SPEED;
	if (strafe_step == 0)
		return ;
	if (strafe_step > 0)
		strafe_angle = table->player_coor->angle + M_PI_2;
	else
		strafe_angle = table->player_coor->angle - M_PI_2;
	*new_x += cos(strafe_angle) * fabs(strafe_step);
	*new_y += sin(strafe_angle) * fabs(strafe_step);
}

void	player_coordonneup(t_table **data)
{
	t_table	*table;
	float	new_x;
	float	new_y;
	float	cur_x;
	float	cur_y;

	table = *data;
	new_x = table->player_coor->position_y * TILE_SIZE;
	new_y = table->player_coor->position_x * TILE_SIZE;
	cur_x = table->player_coor->position_y * TILE_SIZE;
	cur_y = table->player_coor->position_x * TILE_SIZE;
	update_angle(table->player_coor);
	apply_movement(table, &new_x, &new_y);
	apply_strafe(table, &new_x, &new_y);
	if (!has_wall_at(table, new_x, cur_y))
		table->player_coor->position_y = new_x / TILE_SIZE;
	if (!has_wall_at(table, cur_x, new_y))
		table->player_coor->position_x = new_y / TILE_SIZE;
}
