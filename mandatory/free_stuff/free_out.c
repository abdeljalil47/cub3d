/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:33:12 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/27 17:33:13 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

static void	free_elements(t_table *table)
{
	if (table->player_coor)
	{
		free_player(table->player_coor);
		table->player_coor = NULL;
	}
	if (table->map_stru)
	{
		free_map_c(table->map_stru);
		table->map_stru = NULL;
	}
	if (table->map_ele)
	{
		free_map(&table->map_ele);
		table->map_ele = NULL;
	}
}

void	clean_beforeout(t_table **ptable)
{
	t_table	*table;

	if (!ptable || !*ptable)
		return ;
	table = *ptable;
	if (table->img)
		mlx_destroy_image(table->mlx, table->img);
	if (table->mlx_win)
		mlx_destroy_window(table->mlx, table->mlx_win);
	free_elements(table);
	if (table->mlx)
		free(table->mlx);
	free(table);
	*ptable = NULL;
}
