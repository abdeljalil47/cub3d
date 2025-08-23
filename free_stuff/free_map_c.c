#include "../header/cub3d.h"

void free_map_c(map_cub *map)
{
    int i;

    if (!map)
        return;

    if (map->maps)
        free(map->maps);

    if (map->dmaps)
    {
        for (i = 0; map->dmaps[i]; i++)
        {
            free(map->dmaps[i]);
        }
        free(map->dmaps);
        map->dmaps = NULL;
    }
    free(map);
}
