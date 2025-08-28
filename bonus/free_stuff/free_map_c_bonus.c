/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map_c_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:33:17 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:08:26 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

void	free_map_c(t_map_cub *map)
{
	int	i;

	if (!map)
		return ;
	if (map->maps)
		free(map->maps);
	if (map->dmaps)
	{
		i = 0;
		while (map->dmaps[i])
		{
			free(map->dmaps[i]);
			i++;
		}
		free(map->dmaps);
		map->dmaps = NULL;
	}
	free(map);
}
