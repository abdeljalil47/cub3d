/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:09:02 by ahbilla           #+#    #+#             */
/*   Updated: 2025/08/28 15:14:24 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

int	hand_path_frames(t_hand_anim *hand)
{
	int		i;
	char	*path;

	i = 0;
	while (i < HAND_FRAMES_KNIFE)
	{
		path = ft_my_strcat("./bonus/texture_hande/hand/", i + 1, ".xpm");
		if (!path)
			return (free_paths(hand->hand_paths, i), 1);
		hand->hand_paths[i] = ft_strdup(path);
		free(path);
		if (!hand->hand_paths[i])
			return (free_paths(hand->hand_paths, i), 1);
		i++;
	}
	hand_path_frames_mv(hand, path);
	return (0);
}

int	load_weapon_help1(t_table *table)
{
	int	i;

	i = 0;
	while (i < HAND_FRAMES_KNIFE)
	{
		table->handetype->hand_frames[i].img = mlx_xpm_file_to_image(table->mlx,
				table->handetype->hand_paths[i],
				&table->handetype->hand_frames[i].width,
				&table->handetype->hand_frames[i].height);
		if (!table->handetype->hand_frames[i].img)
			return (free_weapon_images(table), 1);
		table->handetype->hand_frames[i].data
			= mlx_get_data_addr(table->handetype->hand_frames[i].img,
				&table->handetype->hand_frames[i].bpp,
				&table->handetype->hand_frames[i].size_line,
				&table->handetype->hand_frames[i].endian);
		if (!table->handetype->hand_frames[i].data)
			return (free_weapon_images(table), 1);
		i++;
	}
	return (0);
}

int	load_weapon_help2(t_table *table)
{
	int	i;

	i = 0;
	while (i < HAND_FRAMES_KNIFE_MV)
	{
		table->handetype->hand_frames_mv[i].img
			= mlx_xpm_file_to_image(table->mlx,
				table->handetype->hand_paths_mv[i],
				&table->handetype->hand_frames_mv[i].width,
				&table->handetype->hand_frames_mv[i].height);
		if (!table->handetype->hand_frames_mv[i].img)
			return (free_weapon_images(table), 1);
		table->handetype->hand_frames_mv[i].data
			= mlx_get_data_addr(table->handetype->hand_frames_mv[i].img,
				&table->handetype->hand_frames_mv[i].bpp,
				&table->handetype->hand_frames_mv[i].size_line,
				&table->handetype->hand_frames_mv[i].endian);
		if (!table->handetype->hand_frames_mv[i].data)
			return (free_weapon_images(table), 1);
		i++;
	}
	return (0);
}

int	load_weapon(t_table *table)
{
	int	i;

	table->handetype->hand_frames
		= malloc(sizeof(t_texture) * HAND_FRAMES_KNIFE);
	if (!table->handetype->hand_frames)
		return (1);
	table->handetype->hand_frames_mv
		= malloc(sizeof(t_texture) * HAND_FRAMES_KNIFE_MV);
	if (!table->handetype->hand_frames_mv)
	{
		free(table->handetype->hand_frames);
		table->handetype->hand_frames = NULL;
		return (1);
	}
	load_weapon_help1(table);
	load_weapon_help2(table);
	i = 0;
	return (0);
}
