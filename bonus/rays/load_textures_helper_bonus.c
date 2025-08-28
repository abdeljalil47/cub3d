/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_helper_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:44:10 by ahbilla           #+#    #+#             */
/*   Updated: 2025/08/28 15:14:27 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

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

int	hand_path_frames_mv(t_hand_anim *hand, char *path)
{
	int	i;

	i = 0;
	while (i < HAND_FRAMES_KNIFE_MV)
	{
		path = ft_my_strcat("./bonus/texture_hande/hand1/", i + 1, ".xpm");
		if (!path)
			return (free_paths(hand->hand_paths_mv, i), 1);
		hand->hand_paths_mv[i] = ft_strdup(path);
		free(path);
		if (!hand->hand_paths_mv[i])
			return (free_paths(hand->hand_paths_mv, i), 1);
		i++;
	}
	return (0);
}
