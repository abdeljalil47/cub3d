#include "../header/cub3d.h"

void    collecte_map(char *line, map_cub **map)
{
	char *back;
	char *map_cole;

	if (!line || !map || !*map)
        return ;
	back = (*map)->maps;
	map_cole = ft_strjoin(back, line);
	if (!map_cole)
		return (free_map_c(*map));
	(*map)->maps = map_cole;
	if (back)
		free(back);
}

int creat_2darray(map_cub **map_c)
{
	if (!map_c)
		return (0);
	(*map_c)->dmaps = ft_split((*map_c)->maps, '\n');
	if (!(*map_c)->dmaps)
		return (0);
	return (1);
}

int check_map_isvalid(map_cub *map_c)
{
	int i;
	int y;

	i = 0;
	while (map_c->dmaps[i])
	{
		y = 0;
		while (map_c->dmaps[i][y])
		{
			if (map_c->dmaps[i][y] != '0' && map_c->dmaps[i][y] != '1'
				&& map_c->dmaps[i][y] != 'N' && map_c->dmaps[i][y] != ' '
				&& map_c->dmaps[i][y] != 'S' && map_c->dmaps[i][y] != 'E'
				&& map_c->dmaps[i][y] != 'W' && map_c->dmaps[i][y] != 'D')
				return (0);
			y++;
		}
		i++;
	}
	return (1);
}

int	find_player(map_cub **map)
{
	int		x;
	int		y;
	map_cub	*map_c;
	int		flag;

	map_c = *map;
	y = 0;
	x = 0;
	flag = 0;
	while (map_c->dmaps[x])
	{
		y = 0;
		while (map_c->dmaps[x][y])
		{
			if (map_c->dmaps[x][y] == 'N' || map_c->dmaps[x][y] == 'S'
				|| map_c->dmaps[x][y] == 'W' || map_c->dmaps[x][y] == 'E')
			{
				flag++;
				(*map)->player_pos->position_x = x + 0.5;
				(*map)->player_pos->position_y = y + 0.5;
			}
			y++;
		}
		x++;
	}
	if (flag != 1 || flag == 0)
		return 0;
	return (1);
}

float	ft_determinate_playerangle(map_cub **map)
{
	int	x;
	int	y;

	x = (int)(*map)->player_pos->position_x;
	y = (int)(*map)->player_pos->position_y;
	if ((*map)->dmaps[x][y] == 'N')
		return (M_PI / 2);
	if ((*map)->dmaps[x][y] == 'S')
		return (-M_PI / 2);
	if ((*map)->dmaps[x][y] == 'E')
		return (0);
	if ((*map)->dmaps[x][y] == 'W')
		return (M_PI);
	return (1);
}

int check_map_bound(char **map)
{
	int i = 0;
	int y = 0;

	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			y++;
		}
		if (y > 100 || i > 100)
			return 0;
		i++;
	}
	return 1;
}

int	check_corner(int y, char **maps, int i)
{
	if (!maps || y == 0 || i == 0)
		return 0;
	if ((maps[i][y] == 'D' && maps[i][y + 1] == 'D')
		|| (maps[i][y] == 'D' && maps[i][y - 1] == 'D')
		|| (maps[i][y] == 'D' && maps[i - 1][y] == 'D')
		|| (maps[i][y] == 'D' && maps[i + 1][y] == 'D'))
		return (ft_putstr_fd("ERROR\nDoor problem (door next to door)\n", 2), 0);
	if ((maps[i][y] == 'D' && (maps[i][y + 1] == '1' && maps[i][y - 1] == '1'))
		|| (maps[i][y] == 'D' && (maps[i + 1][y] == '1' && maps[i - 1][y] == '1')))
		return 1;
	return (ft_putstr_fd("ERROR\ndoor must have wall on corner!\n", 2), 0);
}

int	check_door_with_wall(char **maps)
{
	int	i;
	int y;

	i = 0;
	while (maps[i])
	{
		y = 0;
		while (maps[i][y])
		{
			if (maps[i][y] == 'D' && !check_corner(y, maps, i))
				return 0;
			y++;
		}
		i++;
	}
	return 1;
}

int	handle_map(map_cub **map_c)
{
	if (!check_map_isvalid(*map_c))
		return (ft_putstr_fd("ERROR\nmap not valid!\n", 2), 0);
	if (!find_player(map_c))
		return (ft_putstr_fd("ERROR\nplayer not found or multi-player!\n", 2), 0);
	if (!check_close_map(*map_c))
		return (0);
	if (!check_map_bound((*map_c)->dmaps))
		return (ft_putstr_fd("ERROR\nmax bounds of map is 100*100\n", 2), 0);
	if (!check_door_with_wall((*map_c)->dmaps))
		return (0);
	(*map_c)->player_pos->radius = 3;
	(*map_c)->player_pos->angle = ft_determinate_playerangle(map_c);
	(*map_c)->player_pos->forword_backword = 0;
	(*map_c)->player_pos->leftvu_rightvu = 0;
	(*map_c)->player_pos->rotate = 0;
	(*map_c)->player_pos->player_face = 0;
	(*map_c)->player_pos->player_fov = 0;
	return (1);
}
