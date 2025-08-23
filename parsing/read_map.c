#include "../header/cub3d.h"

static int	init_map_cub(map_cub **map_c)
{
	*map_c = malloc(sizeof(map_cub));
	if (!*map_c)
	{
		ft_putstr_fd("ERROR\nfailed to allocate map\n", 2);
		return (0);
	}
	(*map_c)->maps = NULL;
	(*map_c)->dmaps = NULL;
	(*map_c)->player_pos = malloc(sizeof(player));
	if (!(*map_c)->player_pos)
	{
		free(*map_c);
		ft_putstr_fd("ERROR\nfailed to allocate player\n", 2);
		return (0);
	}
	return (1);
}

static int	free_all(map_valid *map, map_cub *map_c)
{
	if (map_c)
	{
		free_player(map_c->player_pos);
		free_map_c(map_c);
	}
	if (map)
		free_map(&map);
	return (0);
}

int	read_map(char *av)
{
	int			i;
	map_valid	*map;
	map_cub		*map_c;

	if (!av)
		return (ft_putstr_fd("Error\nInvalid map\n", 2), 0);
	map = NULL;
	if (!init_map_cub(&map_c))
		return (0);
	i = 0;
	if (!read_lines(av, &map, &map_c, i))
		return (free_all(map, map_c));
	if (!check_texture_extention(map)
		|| !ft_handle_color(map)
		|| !ft_handle_path(map))
		return (printf("aaaaaaaaaa\n"), free_all(map, map_c));
	if (!creat_2darray(&map_c) || !handle_map(&map_c))
		return (free_all(map, map_c));
	if (!rander_map(&map, &map_c, &map_c->player_pos))
		return (printf("aaaaaaaaaa2\n"), free_all(map, map_c));
	return (free_all(map, map_c), 1);
}
