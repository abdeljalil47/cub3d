#include "../header/cub3d.h"

int	parce_lines(char *tmp, char *prev, char *next, int j)
{
	int i;

	if (!tmp || !prev || !next)//top left right bottom
		return 0;
	i = j;
	// printf("tmp:%s\n", tmp);
	while (tmp[i])
	{
		if (tmp[i] == '1')
		{
			i++;
			continue;
		}
		if ((tmp[i] == '0' || tmp[i] == 'N' || tmp[i] == 'S' || tmp[i] == 'E' || tmp[i] == 'W')
			&& ((int)ft_strlen(prev) < i) && (prev[i] != '1' && prev[i] != '0'
			&& prev[i] != 'N' && prev[i] != 'S' && prev[i] != 'E' && prev[i] != 'W')) //top
			return 0;
		if ((tmp[i] == '0' || tmp[i] == 'N' || tmp[i] == 'S' || tmp[i] == 'E' || tmp[i] == 'W')
			&& (tmp[i + 1] != '0' && tmp[i + 1] != '1'
			&& tmp[i + 1] != 'N' && tmp[i + 1] != 'S' && tmp[i + 1] != 'E' && tmp[i + 1] != 'W')) //left
			return 0;
		if ((tmp[i] == '0' || tmp[i] == 'N' || tmp[i] == 'S' || tmp[i] == 'E' || tmp[i] == 'W')
			&& (tmp[i - 1] != '0' && tmp[i - 1] != '1'
			&& tmp[i - 1] != 'N' && tmp[i - 1] != 'S' && tmp[i - 1] != 'E' && tmp[i - 1] != 'W')) //right
			return 0;
		if ((tmp[i] == '0' || tmp[i] == 'N' || tmp[i] == 'S' || tmp[i] == 'E' || tmp[i] == 'W')
			&& ((int)ft_strlen(next) < i) && (next[i] != '1' && next[i] != '0'
			&& next[i] != 'N' && next[i] != 'S' && next[i] != 'E' && next[i] != 'W')) //bottom
			return 0;
		i++;
	}
	return 1;
}

int	check_close_map(map_cub *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->dmaps[i])
	{
		if (i == 0 && (ft_strchr(map->dmaps[i], '0') || ft_strchr(map->dmaps[i], 'S')
			|| ft_strchr(map->dmaps[i], 'N') || ft_strchr(map->dmaps[i], 'E') || ft_strchr(map->dmaps[i], 'W')))
			return ft_putstr_fd("ERROR\nPlayer in wrong place or invalid structure of walls!\n", 2), 0;
		if ((map->dmaps[i + 1] == NULL) && (ft_strchr(map->dmaps[i], '0') || ft_strchr(map->dmaps[i], 'S')
			|| ft_strchr(map->dmaps[i], 'N') || ft_strchr(map->dmaps[i], 'E') || ft_strchr(map->dmaps[i], 'W')))
			return ft_putstr_fd("ERROR\nPlayer in wrong place or invalid structure of walls!\n", 2), 0;
		j = 0;
		while ((i != 0 || map->dmaps[i + 1] == NULL) && map->dmaps[i][j])
		{
			if (map->dmaps[i][j] == '0' || map->dmaps[i][j] == 'N' || map->dmaps[i][j] == 'S'
				|| map->dmaps[i][j] == 'W' || map->dmaps[i][j] == 'E')
			{
				// printf("%s %d\n", map->dmaps[i], i);
				if (!parce_lines(map->dmaps[i], map->dmaps[i - 1], map->dmaps[i + 1], j))
					return ft_putstr_fd("ERROR\nWorng palcing the map structure!\n", 2), 0;
				else
					break;
			}
			j++;
		}
		i++;
	}
	return 1;
}
