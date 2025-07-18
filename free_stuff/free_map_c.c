#include "../header/cub3d.h"

void	free_map_c(map_cub *map)
{
	int	i;

	if (map->maps)
		free(map->maps);
	if (map->dmaps)
	{
		i = -1;
		while (map->dmaps[++i])
		{
			if (map->dmaps[i])
				free(map->dmaps[i]);
		}
		if (map->dmaps)
			free(map->dmaps);
	}
}
