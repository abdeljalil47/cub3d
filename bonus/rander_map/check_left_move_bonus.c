/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_left_move_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:15:12 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:12:06 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

int	check_left_move(t_table *table, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)((y + MOVE_FAKE) / TILE_SIZE);
	if (map_y < 0 || map_y >= table->height || map_x < 0
		|| map_x >= (int)ft_strlen(table->map_stru->dmaps[map_y]))
		return (1);
	if (table->map_stru->dmaps[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	check_right_move(t_table *table, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)((y - MOVE_FAKE) / TILE_SIZE);
	if (map_y < 0 || map_y >= table->height || map_x < 0
		|| map_x >= (int)ft_strlen(table->map_stru->dmaps[map_y]))
		return (1);
	if (table->map_stru->dmaps[map_y][map_x] == '1')
		return (1);
	return (0);
}
