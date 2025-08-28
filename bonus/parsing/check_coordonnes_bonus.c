/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coordonnes_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:14:46 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:10:10 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

int	ft_divide_line(char *line, char **res)
{
	int	i;
	int	len;

	i = 0;
	while (line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
		i++;
	len = ischaracters(line + i);
	res[0] = ft_substr(line, i, len);
	if (!res[0])
		return (ft_putstr_fd("ERROR\nmalloc failed!\n", 2), 0);
	i += len;
	while (line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
		i++;
	len = 0;
	while (line[i + len])
		len++;
	res[1] = ft_substr(line, i, len);
	if (!res[1])
		return (ft_putstr_fd("ERROR\nmalloc failed!\n", 2), 0);
	return (1);
}

char	**handle_line(char *line)
{
	char	**res;

	res = malloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	res[0] = NULL;
	res[1] = NULL;
	res[2] = NULL;
	if (!ft_divide_line(line, res))
		return (free_res(res), NULL);
	return (res);
}

int	check_duple(t_map_valid *map, char *value)
{
	while (map)
	{
		if (ft_strcmp(map->type, value) == 0)
			return (0);
		map = map->next;
	}
	return (1);
}

int	handle_cordonnes(char *line, t_map_valid **map)
{
	char	**res;

	res = handle_line(line);
	if (!res)
		return (0);
	if (ft_strlen(res[0]) == 1)
	{
		if (ft_strcmp(res[0], "N") != 0 && ft_strcmp(res[0], "S") != 0
			&& ft_strcmp(res[0], "W") != 0 && ft_strcmp(res[0], "E") != 0
			&& ft_strcmp(res[0], "F") != 0 && ft_strcmp(res[0], "C") != 0)
			return (free_res(res), ft_putstr_fd("ERROR\nBad \
coordonnes\n", 2), 0);
	}
	else
	{
		if (ft_strcmp(res[0], "NO") != 0 && ft_strcmp(res[0], "SO") != 0
			&& ft_strcmp(res[0], "WE") != 0 && ft_strcmp(res[0], "EA") != 0
			&& ft_strcmp(res[0], "F") != 0 && ft_strcmp(res[0], "C") != 0)
			return (free_res(res), ft_putstr_fd("ERROR\nBad \
coordonnes\n", 2), 0);
	}
	if (!check_duple(*map, res[0]))
		return (free_res(res), ft_putstr_fd("ERROR\nthe coordonner \
are duplicated!\n", 2), 0);
	return (init_map(map, res), free_res(res), 1);
}

int	check_type_cordonnes(t_map_valid *lst)
{
	int			i;
	t_map_valid	*map;
	int			flag;

	i = 0;
	flag = 0;
	map = lst;
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
		return (1);
	return (0);
}
