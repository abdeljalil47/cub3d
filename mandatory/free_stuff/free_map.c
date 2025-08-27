/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:33:14 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/27 17:33:15 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	free_map(t_map_valid **maps)
{
	t_map_valid	*tmp;
	t_map_valid	*map;

	if (maps == NULL)
		return ;
	map = *maps;
	while (map)
	{
		tmp = map->next;
		if (map->color)
			free(map->color);
		if (map->path)
			free(map->path);
		if (map->type)
			free(map->type);
		free(map);
		map = tmp;
	}
	*maps = NULL;
}
