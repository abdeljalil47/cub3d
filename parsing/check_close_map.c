#include "../header/cub3d.h"

int	ischaracters(char *line)
{
    int	i;

	i = 0;
    while (line[i] && !(line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
        i++;
    return (i);
}

int	parce_lines(char *tmp, char *prev, char *next, int j)
{
	if (!tmp || !prev || !next)
		return (0);
	while (tmp[j])
	{
		if (tmp[j] == '1')
		{
			j++;
			continue;
		}
		if (!check_prev(j, tmp, prev, next))
			return (0);
		j++;
	}
	return (1);
}

int	check_bpund_map(map_cub *map, int i)
{
	if (i == 0 && (ft_strchr(map->dmaps[i], '0')
			|| ft_strchr(map->dmaps[i], 'S')
			|| ft_strchr(map->dmaps[i], 'N') || ft_strchr(map->dmaps[i], 'E')
			|| ft_strchr(map->dmaps[i], 'W')))
		return (ft_putstr_fd("ERROR\nPlayer in wrong place or \
invalid structure of walls!\n", 2), 0);
	if ((map->dmaps[i + 1] == NULL) && (ft_strchr(map->dmaps[i], '0')
			|| ft_strchr(map->dmaps[i], 'S')
			|| ft_strchr(map->dmaps[i], 'N') || ft_strchr(map->dmaps[i], 'E')
			|| ft_strchr(map->dmaps[i], 'W')))
		return (ft_putstr_fd("ERROR\nPlayer in wrong place or \
invalid structure of walls!\n", 2), 0);
	return (1);
}

int	check_close_map(map_cub *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->dmaps[i])
	{
		if (!check_bpund_map(map, i))
			return (0);
		j = 0;
		while ((i != 0 || map->dmaps[i + 1] == NULL) && map->dmaps[i][j])
		{
			if (map->dmaps[i][j] == '0' || map->dmaps[i][j] == 'N' || map->dmaps[i][j] == 'S'
				|| map->dmaps[i][j] == 'W' || map->dmaps[i][j] == 'E')
			{
				if (!parce_lines(map->dmaps[i], map->dmaps[i - 1], map->dmaps[i + 1], j))
					return (ft_putstr_fd("ERROR\nWorng palcing the map structure!\n", 2), 0);
				else
					break;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_handle_path(map_valid *val)
{
	int			fd;
	map_valid	*check;
	int			i;

	if (!val)
		return (0);
	check = val;
	i = 0;
	while (check)
	{
		if (check->coordonne == 1 && i != 4)
		{
			fd = open(check->path, O_RDONLY);
			if (fd == -1)
				return (ft_putstr_fd("ERROR\nCan't open the file '", 2)
					, write(2, check->path, ft_strlen(check->path))
					, write(2, "'\n", 2), 0);
			close(fd);
			i++;
		}
		check = check->next;
	}
	return (1);
}
