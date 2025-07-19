#include "../header/cub3d.h"

int ft_handle_path(map_valid *val)
{
	int fd;
	map_valid *check = val;

	while (check)
	{
		if (!val || !ft_strnstr(check->path, "./", 2))
			return ft_putstr_fd("ERROR\nTexture path dont have './'\n", 2), 0;
		fd = open(check->path, O_DIRECTORY | O_RDONLY);
		if (fd == -1)
			return ft_putstr_fd("ERROR\nCan't open the file '", 2)
				, write(2, check->path, ft_strlen(check->path)), write(2, "'\n", 2), 0;
		check = check->next;
	}
	return 1;
}

int ft_color_rgb(map_valid **map)
{
	char **res;
	int i = 0;
	int j = 0;

	res = ft_split((*map)->color, ',');
	if (!res)
		return 0;
	while (res[i])
	{
		j = 0;
		printf("%d\n", ft_atoi(res[i]));
		while (res[i][j])
		{
			if (res[i][j] == '+' || res[i][j] == '-')
				j++;
			if (!ft_isdigit(res[i][j]))
				return ft_putstr_fd("ERROR\nColor RGB not a digit\n", 2), free_res(res), 0;
			j++;
		}
		if (ft_atoi(res[i]) < 0)
			return ft_putstr_fd("ERROR\nNegative RGB not allowed!\n", 2), free_res(res),  0;
		if (!(ft_atoi(res[i]) >= 0 && ft_atoi(res[i]) <= 255))
			return ft_putstr_fd("ERROR\nOut of range RGB '[0 - 255]'\n", 2), free_res(res), 0;
		i++;
	}
	if (res[0] && res[1] && res[2])
		(*map)->color_rgb = ft_atoi(res[0]) << 16 | ft_atoi(res[1]) << 8 | ft_atoi(res[2]) << 0;
	printf("vv:%X\n", (*map)->color_rgb);
	free_res(res);
	return 1;
}

int ft_handle_color(map_valid *map)
{
	map_valid *color;
	int j;
	int comma;

	color = map;
	while (color)
	{
		j = 0;
		comma = 0;
		if (!ft_strcmp(color->type, "F") || !ft_strcmp(color->type, "C"))
		{
			while (color->color[j])
			{
				if (color->color[j] == ',' && color->color[j + 1] == ',')
					return ft_putstr_fd("ERROR\nColor RGB incorrect\n", 2), 0;
				if (color->color[j] == ',')
					comma++;
				j++;
			}
			if (comma > 2)
				return ft_putstr_fd("ERROR\nMore Comma\n", 2), 0;
			if (!ft_color_rgb(&color))
				return 0;
		}
		color = color->next;
	}
	return 1;
}

int ischaracters(char *line)
{
    int i;

	i = 0;
    while (line[i] && !(line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
        i++;
    return i;
}

int ft_divide_line(char *line, char **res)
{
    int i;
	int len;

	i = 0;
    while (line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
        i++;
    len = ischaracters(line + i);
    res[0] = ft_substr(line, i, len);
	if (!res[0])
		return ft_putstr_fd("ERROR\nmalloc failed!\n", 2), 0;
    i += len;
    while (line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
        i++;
    len = 0;
    while (line[i + len])
        len++;
    res[1] = ft_substr(line, i, len);
	if (!res[1])
		return ft_putstr_fd("ERROR\nmalloc failed!\n", 2), 0;
	return 1;
}

char **handle_line(char *line)
{
    char **res;

    res = malloc(sizeof(char *) * 3);
    if (!res)
        return NULL;
    res[0] = NULL;
    res[1] = NULL;
    res[2] = NULL;
    if (!ft_divide_line(line, res))
		return free_res(res), NULL;
    return res;
}
int check_duple(map_valid *map, char *value)
{
	while (map)
	{
		if (ft_strcmp(map->type, value) == 0)
			return 0;
		map = map->next;
	}
	return 1;
}
int handle_cordonnes(char *line, map_valid **map)
{
	char **res;

	res = handle_line(line);
	if (!res)
		return 0;
	if (ft_strlen(res[0]) == 1)
	{
		if (ft_strcmp(res[0], "N") != 0 && ft_strcmp(res[0], "S") != 0
			&& ft_strcmp(res[0], "W") != 0 && ft_strcmp(res[0], "E") != 0
			&& ft_strcmp(res[0], "F") != 0 && ft_strcmp(res[0], "C") != 0)
			return free_res(res), ft_putstr_fd("ERROR\nBad coordonnes\n", 2), 0;
	}
	else
	{
		if (ft_strcmp(res[0], "NO") != 0 && ft_strcmp(res[0], "SO") != 0
			&& ft_strcmp(res[0], "WE") != 0 && ft_strcmp(res[0], "EA") != 0
			&& ft_strcmp(res[0], "F") != 0 && ft_strcmp(res[0], "C") != 0)
			return free_res(res), ft_putstr_fd("ERROR\nBad coordonnes\n", 2), 0;
	}
	if (!check_duple(*map, res[0]))
		return free_res(res), ft_putstr_fd("ERROR\nthe coordonner are duplicated!\n", 2),0;
	init_map(map, res);
	free_res(res);
	return 1;
}

int	check_type_cordonnes(map_valid *lst)
{
	int	i;
	map_valid *map = lst;
	int flag;

	i = 0;
	flag = 0;
	if (!lst)
		return (1);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	while (map)
	{
		if (map->coordonne == true)
			flag++;
		map = map->next;
	}
	if (flag != 6)
		return 1;
	return 0;
}

int	read_map(char *av)
{
	int			fd;
	char		*line;
	int			i;
	map_valid	*map;
	map_cub		*map_c;

	map = NULL;
	map_c = malloc(sizeof(map_cub));
	if (!map_c)
		return ft_putstr_fd("ERROR\nfailed to allocate map\n", 2), 0;
	map_c->maps = NULL;
	map_c->dmaps = NULL;
	map_c->player_pos = malloc(sizeof(player));
	if (!map_c->player_pos)
		return free(map_c), ft_putstr_fd("ERROR\nfailed to allocate player\n", 2), 0;
	i = 0;
	if (!av)
		return (ft_putstr_fd("Error\nInvalid map\n", 2), free(map_c), free(map), 0);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nmap not found\n", 2), free(map_c), free(map), 0);
	line = get_next_line(fd);
	if (!line)
		return (ft_putstr_fd("Error\nread function failed!\n", 2), free(map_c), free(map), 0);
	while (line)
	{
		if (map_c->maps && !ft_strcmp(line, "\n"))
			return (free_map_c(map_c), free_map(&map), free_player(map_c->player_pos),
				free(map_c), ft_putstr_fd("Error\nInvalid file (more new lines)!\n", 2), 0);
		if (!ft_strcmp(line, "\n"))
		{
			free(line), line = get_next_line(fd);
			continue;
		}
		else if (check_type_cordonnes(map))
		{
			if (!handle_cordonnes(line, &map))
				return (free(line), free_map_c(map_c), free_map(&map), free_player(map_c->player_pos), free(map_c), 0);
			i++;
		}
		else
			collecte_map(line, &map_c);
		if (i == 0)
			return free_map_c(map_c), free_map(&map), free_player(map_c->player_pos),
				free(map_c), ft_putstr_fd("ERROR\nMap file doesn't respects the structure or bad cordonnes!\n", 2), 0;
		free(line);
		line = get_next_line(fd);
	}
	map_valid *current = map;
	while (current)
	{
		printf("%s<>%s<>%d\n", current->type, current->path, current->coordonne);
		if (ft_strcmp(current->type, "F") == 0 || ft_strcmp(current->type, "C") == 0)
			printf("\taaaaaaa:%s\n", current->color);
		current=current->next;
	}
	if (!check_texture_extention(map) || !ft_handle_color(map))// || !ft_handle_path(map)
		return free_map_c(map_c), free_map(&map), free_player(map_c->player_pos), free(map_c), 0;
	if (!creat_2darray(&map_c) || !handle_map(&map_c))
		return free_map_c(map_c), free_map(&map), free_player(map_c->player_pos), free(map_c), 0;
	return free_map_c(map_c), free_player(map_c->player_pos), free_map(&map), free(map_c), 1;//test free's functions.
}
