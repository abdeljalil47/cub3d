/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_top_move_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:15:16 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:12:08 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

int	check_top_move(t_table *table, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)((x - MOVE_FAKE) / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0 || map_y >= table->height
		|| map_x >= (int)ft_strlen(table->map_stru->dmaps[map_y]))
		return (1);
	if (table->map_stru->dmaps[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	check_bottom_move(t_table *table, float x, float y)
{
	int	map_x;
	int	map_y;

	map_y = (int)(y / TILE_SIZE);
	map_x = (int)((x + MOVE_FAKE) / TILE_SIZE);
	if (map_x < 0 || map_y < 0 || map_y >= table->height
		|| map_x >= (int)ft_strlen(table->map_stru->dmaps[map_y]))
		return (1);
	if (table->map_stru->dmaps[map_y][map_x] == '1')
		return (1);
	return (0);
}
