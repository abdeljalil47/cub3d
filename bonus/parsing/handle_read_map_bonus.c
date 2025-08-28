/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_read_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:14:33 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:10:41 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

static int	check_empty_line(char *line, t_map_cub **map_c,
			int fd)
{
	int	i;
	int	count;

	if (line && (*map_c)->maps && (!ft_strcmp(line, "\n")
			|| !ft_strcmp(line, " ")))
	{
		ft_putstr_fd("Error\nInvalid file (more new lines)!\n", 2);
		return (close(fd), free(line), 0);
	}
	else if (line && (*map_c)->maps)
	{
		i = 0;
		count = 0;
		while (line[i] && i < (int)ft_strlen(line))
		{
			if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
				count = 0;
			i++;
			count++;
		}
		if (i == count)
			return (close(fd), free(line), 0);
	}
	return (1);
}

int	check_line_in(int *i)
{
	if (*i == 0)
		return (ft_putstr_fd("ERROR\nMap file doesn't respects \
the structure or bad cordonnes!\n", 2), 0);
	return (1);
}

int	check_all(t_map_valid **map, char *line, t_map_cub **map_c, int *i)
{
	if (check_type_cordonnes(*map))
	{
		if (!handle_cordonnes(line, map))
			return (free(line), 0);
		(*i)++;
	}
	else
		collecte_map(line, map_c);
	return (1);
}

static char	*open_read_first_line(int *fd, char **line, char *av)
{
	*fd = open(av, O_RDONLY);
	if (*fd == -1)
	{
		ft_putstr_fd("Error\nMap not found\n", 2);
		return (NULL);
	}
	*line = get_next_line(*fd);
	if (!*line)
	{
		ft_putstr_fd("Error\nRead lines failed!\n", 2);
		close(*fd);
		return (NULL);
	}
	return (*line);
}

int	read_lines(char *av, t_map_valid **map, t_map_cub **map_c, int i)
{
	int		fd;
	char	*line;

	i = 0;
	if (!open_read_first_line(&fd, &line, av))
		return (0);
	while (line)
	{
		if (!check_empty_line(line, map_c, fd))
			return (0);
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!check_all(map, line, map_c, &i))
			return (close(fd), 0);
		if (!check_line_in(&i))
			return (close(fd), 0);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
