#include "../header/cub3d.h"

int	check_type(char **res, int flag)
{
	if (flag == 0)
	{
		if (ft_strlen(res[0]) == 1)
		{
			if (ft_strcmp(res[0], "N") == 0 || ft_strcmp(res[0], "S") == 0
				|| ft_strcmp(res[0], "W") == 0 || ft_strcmp(res[0], "E") == 0)
				return (1);
		}
		else
		{
			if (ft_strcmp(res[0], "NO") == 0 || ft_strcmp(res[0], "SO") == 0
				|| ft_strcmp(res[0], "WE") == 0 || ft_strcmp(res[0], "EA") == 0)
				return (1);
		}
	}
	else
	{
		if (ft_strncmp(res[0], "F", ft_strlen(res[0])) == 0
			|| ft_strncmp(res[0], "C", ft_strlen(res[0])) == 0)
			return (1);
	}
	return (0);
}

void	init_map(map_valid **map, char **value)
{
	map_valid	*element;
	map_valid	*current;

	element = malloc(sizeof(map_valid));
	if (element == NULL)
	{
		if (map || *map)
			return (free_map(map));
		else
			exit(1);
	}
	element->next = NULL;
	element->color_rgb = 0;
	element->type = ft_strndup(value[0], ft_strlen(value[0]));

	if (check_type(value, 0))
	{
		element->path = ft_strndup(value[1], ft_strlen(value[1]) - 1);
		element->color = ft_strdup("\0");
		element->coordonne = true;
	}
	if (check_type(value, 1))
	{
		element->path = ft_strdup("\0");
		element->color = ft_strndup(value[1], ft_strlen(value[1]) - 1);
		element->coordonne = true;
	}
	if (!element->type || !element->path || !element->color)
	{
		if (element->type)
			free(element->type);
		if (element->path)
			free(element->path);
		if (!element->color)
			free(element->color);
		return free(element);
	}
	if (!*map)
		*map = element;
	else
	{
		current = *map;
		while (current->next != NULL)
			current = current->next;
		current->next = element;
	}
}
