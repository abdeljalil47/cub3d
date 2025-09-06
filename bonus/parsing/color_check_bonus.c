/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:14:36 by abdsebba          #+#    #+#             */
/*   Updated: 2025/09/06 20:36:17 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

long	ft_atoi_handle_over(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		if ((result * sign) > INT_MAX || (result * sign) < INT_MIN)
			return (INT_MAX + (long)1);
		i++;
	}
	return (sign * result);
}

int	check_color_input(int i, int j, char **res)
{
	while (res[i][j])
	{
		if (res[i][j] == '+' || res[i][j] == '-')
			j++;
		if (!ft_isdigit(res[i][j]))
			return (ft_putstr_fd("ERROR\nColor RGB \
not a digit\n", 2), 0);
		j++;
	}
	if (ft_atoi_handle_over(res[i]) > INT_MAX
		|| ft_atoi_handle_over(res[i]) < INT_MIN)
		return (ft_putstr_fd("ERROR\nNegative RGB \
not allowed!\n", 2), 0);
	return (1);
}

int	ft_color_rgb(t_map_valid **map)
{
	char	**res;
	int		i;
	int		j;

	res = ft_split((*map)->color, ',');
	if (!res)
		return (0);
	i = 0;
	while (res[i])
	{
		j = 0;
		if (!check_color_input(i, j, res))
			return (free_res(res), 0);
		if (!(ft_atoi(res[i]) >= 0 && ft_atoi(res[i]) <= 255))
			return (ft_putstr_fd("ERROR\nOut of range \
RGB '[0 - 255]'\n", 2), free_res(res), 0);
		i++;
	}
	if (count_height(res) != 3)
		return (free_res(res), ft_putstr_fd("ERROR\nNot enough \
arguments\n", 2), 0);
	if (res[0] && res[1] && res[2])
		((*map)->color_rgb = ft_atoi(res[0]) << 16
				| ft_atoi(res[1]) << 8 | ft_atoi(res[2]) << 0);
	return (free_res(res), 1);
}

int	ft_handle_color(t_map_valid *map)
{
	int	j;
	int	comma;

	while (map)
	{
		j = 0;
		comma = 0;
		if (!ft_strcmp(map->type, "F") || !ft_strcmp(map->type, "C"))
		{
			while (map->color[j])
			{
				if (map->color[j] == ',' && map->color[j + 1] == ',')
					return (ft_putstr_fd("ERROR\nIncorrect Color\n", 2), 0);
				if (map->color[j] == ',')
					comma++;
				j++;
			}
			if (comma != 2)
				return (ft_putstr_fd("ERROR\nMore or No Comma\n", 2), 0);
			if (!ft_color_rgb(&map))
				return (0);
		}
		map = map->next;
	}
	return (1);
}
