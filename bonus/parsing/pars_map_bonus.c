/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:14:26 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:10:47 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

char	*ft_str_extantion(char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	--i;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i--;
	}
	if ((char)c == '\0')
		return ((char *)(str));
	return (NULL);
}

int	check_map_extention(char *av)
{
	if (!av)
		return (ft_putstr_fd("Error\nInvalid map\n", 2), -1);
	if (ft_strchr(av, 32) || av[0] == '\0' || av[0] == '.'
		|| !ft_strchr(av, '.'))
		return (ft_putstr_fd("Error\nInvalid map\n", 2), 0);
	if (ft_strcmp(ft_str_extantion(av, '.'), ".cub") != 0)
		return (ft_putstr_fd("Error\nInvalid map\n", 2), 0);
	return (read_map(av));
}

int	check_texture_extention(t_map_valid *av)
{
	t_map_valid	*texture;

	texture = av;
	if (!av)
		return (ft_putstr_fd("Error\nInvalid texture\n", 2), 0);
	while (texture)
	{
		if (texture->path && texture->color[0] == '\0'
			&& (texture->path[0] == '\0'
				|| !ft_strchr(texture->path, '.')))
			return (ft_putstr_fd("Error\nInvalid texture\n", 2), 0);
		if (texture->path && texture->color[0] == '\0'
			&& (ft_strcmp(ft_str_extantion(texture->path, '.'), ".xpm") != 0))
			return (ft_putstr_fd("Error\nInvalid texture '", 2)
				, ft_putstr_fd(texture->path, 2), write(2, "'\n", 2), 0);
		texture = texture->next;
	}
	return (1);
}
