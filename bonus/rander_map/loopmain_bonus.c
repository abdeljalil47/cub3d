/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loopmain_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:09:29 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:46:23 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

int	mainloop(void *param)
{
	t_table	*table;

	table = (t_table *)param;
	player_coordonneup(&table);
	ft_put_player(&table);
	cast_all_rays(table);
	put_texture(table);
	return (0);
}

int	count_height(char **line)
{
	int	i;

	if (!line)
		return (-1);
	i = 0;
	while (line[i])
	{
		i++;
	}
	return (i);
}

int	close_window(void *param)
{
	t_table	*table;
	int		i;

	table = (t_table *)param;
	i = 0;
	while (i < 4)
	{
		if (table->textures[i].img)
			mlx_destroy_image(table->mlx, table->textures[i].img);
		i++;
	}
	free_paths(table->handetype->hand_paths, HAND_FRAMES_KNIFE);
	free_paths(table->handetype->hand_paths_mv, HAND_FRAMES_KNIFE_MV);
	free_weapon_images(table);
	free(table->handetype);
	free(table->tex_path);
	clean_beforeout(&table);
	exit(0);
	return (0);
}

void	cast_all_rays(t_table *table)
{
	float	ray_angle;
	int		i;

	ray_angle = table->player_coor->angle - (FOV_ANGLE / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		if (!cast_rays(table, ray_angle, i))
			return ;
		ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}

int	mouse_move(int x, int y, t_table *table)
{
	double	sensitivity;
	int		delta_x;

	(void)y;
	sensitivity = 0.004;
	if (table->last_x == -1)
		table->last_x = x;
	delta_x = x - table->last_x;
	table->player_coor->angle += delta_x * sensitivity;
	table->last_x = x;
	return (0);
}
