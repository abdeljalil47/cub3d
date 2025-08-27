/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:44:10 by ahbilla           #+#    #+#             */
/*   Updated: 2025/08/27 18:35:12 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

static void	free_textures(t_table *table, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (table->textures[i].img)
			mlx_destroy_image(table->mlx, table->textures[i].img);
		i++;
	}
}

static int	load_one_texture(t_table *table, int i, char *path)
{
	table->textures[i].img = mlx_xpm_file_to_image(table->mlx, path,
			&table->textures[i].width, &table->textures[i].height);
	if (!table->textures[i].img)
		return (1);
	table->textures[i].data = mlx_get_data_addr(table->textures[i].img,
			&table->textures[i].bpp,
			&table->textures[i].size_line,
			&table->textures[i].endian);
	if (!table->textures[i].data)
	{
		mlx_destroy_image(table->mlx, table->textures[i].img);
		return (1);
	}
	return (0);
}

int	load_textures(t_table *table)
{
	int		i;
	char	*paths[4];

	paths[0] = table->tex_path->wall_no;
	paths[1] = table->tex_path->wall_so;
	paths[2] = table->tex_path->wall_we;
	paths[3] = table->tex_path->wall_ea;
	i = 0;
	while (i < 4)
	{
		if (load_one_texture(table, i, paths[i]))
		{
			free_textures(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}
