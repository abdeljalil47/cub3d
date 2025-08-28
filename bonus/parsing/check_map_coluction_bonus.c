/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_coluction_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:14:44 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:10:18 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

int	check_element(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	check_map_bound(char **map)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			y++;
		}
		if (y > 100 || i > 100)
			return (0);
		i++;
	}
	return (1);
}

int	check_prev(int j, char *tmp, char *prev, char *next)
{
	if ((tmp[j] == '0' || tmp[j] == 'N' || tmp[j] == 'S'
			|| tmp[j] == 'E' || tmp[j] == 'W') && (((int)ft_strlen(prev) < j)
			|| (prev[j] != '1' && prev[j] != '0' && prev[j] != 'N'
				&& prev[j] != 'S' && prev[j] != 'E' && prev[j] != 'W')))
		return (0);
	if ((tmp[j] == '0' || tmp[j] == 'N' || tmp[j] == 'S' || tmp[j] == 'E'
			|| tmp[j] == 'W') && (tmp[j + 1] != '0' && tmp[j + 1] != '1'
			&& tmp[j + 1] != 'N' && tmp[j + 1] != 'S' && tmp[j + 1] != 'E'
			&& tmp[j + 1] != 'W'))
		return (0);
	if ((tmp[j] == '0' || tmp[j] == 'N' || tmp[j] == 'S' || tmp[j] == 'E'
			|| tmp[j] == 'W') && (tmp[j - 1] != '0' && tmp[j - 1] != '1'
			&& tmp[j - 1] != 'N' && tmp[j - 1] != 'S' && tmp[j - 1] != 'E'
			&& tmp[j - 1] != 'W'))
		return (0);
	if ((tmp[j] == '0' || tmp[j] == 'N' || tmp[j] == 'S' || tmp[j] == 'E'
			|| tmp[j] == 'W') && (((int)ft_strlen(next) < j) || (next[j] != '1'
				&& next[j] != '0' && next[j] != 'N' && next[j] != 'S'
				&& next[j] != 'E' && next[j] != 'W')))
		return (0);
	return (1);
}

int	check_map_isvalid(t_map_cub *map_c)
{
	int	i;
	int	y;

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
				return (0);
			y++;
		}
		i++;
	}
	return (1);
}
