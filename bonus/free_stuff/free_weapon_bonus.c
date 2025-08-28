/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_weapon_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:33:02 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:09:08 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

static void	free_mv(t_table *table)
{
	int	i;

	if (table->handetype->hand_frames_mv)
	{
		i = 0;
		while (i < HAND_FRAMES_KNIFE_MV)
		{
			if (table->handetype->hand_frames_mv[i].img)
				mlx_destroy_image(table->mlx,
					table->handetype->hand_frames_mv[i].img);
			i++;
		}
		free(table->handetype->hand_frames_mv);
		table->handetype->hand_frames_mv = NULL;
	}
}

void	free_weapon_images(t_table *table)
{
	int	i;

	if (!table || !table->handetype)
		return ;
	if (table->handetype->hand_frames)
	{
		i = 0;
		while (i < HAND_FRAMES_KNIFE)
		{
			if (table->handetype->hand_frames[i].img)
				mlx_destroy_image(table->mlx,
					table->handetype->hand_frames[i].img);
			i++;
		}
		free(table->handetype->hand_frames);
		table->handetype->hand_frames = NULL;
	}
	free_mv(table);
}
