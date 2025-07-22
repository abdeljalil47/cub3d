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
		return free_map_c(*map);
	(*map)->maps = map_cole;
	if (back)
		free(back);
}

int creat_2darray(map_cub **map_c)
{
	if (!map_c)
		return 0;
	(*map_c)->dmaps = ft_split((*map_c)->maps, '\n');
	if (!(*map_c)->dmaps)
		return 0;
	return 1;
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
				&& map_c->dmaps[i][y] != 'W')
				return 0;
			y++;
		}
		i++;
	}
	return 1;
}

int find_player(map_cub **map)
{
	int x;
	int y;
	map_cub *map_c;
	int flag;

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
				(*map)->player_pos->position_x = x;
				(*map)->player_pos->position_y = y;
			}
			y++;
		}
		x++;
	}
	if (flag != 1 || flag == 0)
		return 0;
	return (1);
}

int handle_map(map_cub **map_c)
{
	if (!check_map_isvalid(*map_c))
		return ft_putstr_fd("ERROR\nmap not valid!\n", 2), 0;
	if (!find_player(map_c))
		return ft_putstr_fd("ERROR\nplayer not found or multi-player!\n", 2), 0;
	(*map_c)->player_pos->radius = 3;
	(*map_c)->player_pos->angle = M_PI / 2;
	(*map_c)->player_pos->rotation_speed = 2 * (M_PI / 180);
	(*map_c)->player_pos->forword_backword = 0;
	(*map_c)->player_pos->leftword_rightword = 0;
	printf("X:%d\n", (*map_c)->player_pos->position_x);
	printf("Y:%d\n", (*map_c)->player_pos->position_y);
	if (!check_close_map(*map_c))
		return 0;
	return 1;
}
