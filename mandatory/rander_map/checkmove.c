/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:14:19 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/27 17:14:20 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

static int	ft_move_check(t_table *table, float x, float y)
{
	if (check_top_move(table, x, y)
		|| check_bottom_move(table, x, y)
		|| check_left_move(table, x, y)
		|| check_right_move(table, x, y))
		return (1);
	return (0);
}

int	has_wall_at(t_table *table, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_x >= table->width || map_y >= table->height)
		return (1);
	if (table->map_stru->dmaps[map_y][map_x] == '1')
		return (1);
	if (ft_move_check(table, x, y))
		return (1);
	return (0);
}
