/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loopmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:09:29 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 14:04:29 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	put_pixel(t_table *table, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = table->img_data + (y * table->size_line + x * (table->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	mainloop(void *param)
{
	t_table	*table;

	table = (t_table *)param;
	player_coordonneup(&table);
	cast_all_rays(table);
	render_3d_projection(table);
	mlx_put_image_to_window(table->mlx, table->mlx_win, table->img, 0, 0);
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
