#include "../header/cub3d.h"

void	free_map(map_valid **maps)
{
    map_valid	*tmp;
    map_valid	*map;

    if (maps == NULL)
        return;
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
