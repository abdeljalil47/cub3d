/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:16:07 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:38:40 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

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

static void	init_validelement(t_map_valid **elem, char **value)
{
	t_map_valid	*element;

	element = *elem;
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
}

static void	addback(t_map_valid *element, t_map_valid **map)
{
	t_map_valid	*current;

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

void	init_map(t_map_valid **map, char **value)
{
	t_map_valid	*element;

	element = malloc(sizeof(t_map_valid));
	if (element == NULL)
	{
		if (map || *map)
			return (free_map(map));
		else
			return ;
	}
	init_validelement(&element, value);
	if (!element->type || !element->path || !element->color)
	{
		if (element->type)
			free(element->type);
		if (element->path)
			free(element->path);
		if (!element->color)
			free(element->color);
		return (free(element));
	}
	addback(element, map);
}
