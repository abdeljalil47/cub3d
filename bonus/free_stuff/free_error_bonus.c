/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:33:19 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:08:11 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

static void	free_table(t_table *table)
{
	mlx_destroy_window(table->mlx, table->mlx_win);
	mlx_destroy_image(table->mlx, table->img);
	free(table->mlx);
	free(table->tex_path);
	free(table->handetype);
	free(table);
}

void	free_onerror(t_table *table, int flag)
{
	int	i;

	if (flag == 1)
	{
		i = 0;
		while (i < 4)
		{
			if (table->textures[i].img)
				mlx_destroy_image(table->mlx, table->textures[i].img);
			i++;
		}
	}
	else if (flag == 2)
	{
		free_paths(table->handetype->hand_paths, HAND_FRAMES_KNIFE);
		free_paths(table->handetype->hand_paths_mv, HAND_FRAMES_KNIFE_MV);
		i = 0;
		while (i < 4)
		{
			if (table->textures[i].img)
				mlx_destroy_image(table->mlx, table->textures[i].img);
			i++;
		}
	}
	free_table(table);
}
