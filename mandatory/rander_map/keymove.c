/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:14:09 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/27 18:53:23 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

static void	handle_exit(t_table *table, int key)
{
	int	i;

	if (key == KEY_ESC)
	{
		i = 0;
		while (i < 4)
		{
			if (table->textures[i].img)
				mlx_destroy_image(table->mlx, table->textures[i].img);
			i++;
		}
		free(table->tex_path);
		clean_beforeout(&table);
		exit(0);
	}
}

static void	reset_movement(t_table *table, int key)
{
	if (key == KEY_RELEASE_1 || key == KEY_RELEASE_2)
	{
		table->player_coor->forword_backword = 0;
		table->player_coor->leftvu_rightvu = 0;
		table->player_coor->rotate = 0;
	}
}

static void	update_movement(t_table *table, int key)
{
	if (key == KEY_S)
		table->player_coor->forword_backword = -1;
	else if (key == KEY_W)
		table->player_coor->forword_backword = 1;
	else if (key == KEY_D)
		table->player_coor->leftvu_rightvu = 1;
	else if (key == KEY_A)
		table->player_coor->leftvu_rightvu = -1;
	else if (key == ARROW_LEFT)
		table->player_coor->rotate = -1;
	else if (key == ARROW_RIGHT)
		table->player_coor->rotate = 1;
}

int	keycode(int key, void *param)
{
	t_table	*table;

	table = (t_table *)param;
	if (!table)
		return (0);
	reset_movement(table, key);
	handle_exit(table, key);
	update_movement(table, key);
	return (0);
}
