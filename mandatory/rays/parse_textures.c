/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:17:42 by ahbilla           #+#    #+#             */
/*   Updated: 2025/08/27 16:28:23 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	find_ceiling_floor(t_table *table, int *c, int *f)
{
	int			ceiling;
	int			floor;
	t_map_valid	*map;

	ceiling = -1;
	floor = -1;
	map = table->map_ele;
	while (map)
	{
		if (map->type && ft_strcmp(map->type, "F") == 0)
			floor = map->color_rgb;
		else if (map->type && ft_strcmp(map->type, "C") == 0)
			ceiling = map->color_rgb;
		map = map->next;
	}
	*c = ceiling;
	*f = floor;
}

void	find_texture_wall_angle(t_table *table)
{
	t_map_valid	*wall;

	if (!table || !table->map_ele)
		return ;
	wall = table->map_ele;
	while (wall)
	{
		if ((ft_strcmp(wall->type, "NO") == 0)
			|| (ft_strcmp(wall->type, "N") == 0))
			table->tex_path->wall_no = wall->path;
		else if ((ft_strcmp(wall->type, "SO") == 0)
			|| (ft_strcmp(wall->type, "S") == 0))
			table->tex_path->wall_so = wall->path;
		else if ((ft_strcmp(wall->type, "WE") == 0)
			|| (ft_strcmp(wall->type, "W") == 0))
			table->tex_path->wall_we = wall->path;
		else if ((ft_strcmp(wall->type, "EA") == 0)
			|| (ft_strcmp(wall->type, "E") == 0))
			table->tex_path->wall_ea = wall->path;
		wall = wall->next;
	}
}
