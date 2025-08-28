/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collecte_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:14:41 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:10:27 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

void	collecte_map(char *line, t_map_cub **map)
{
	char	*back;
	char	*map_cole;

	if (!line || !map || !*map)
		return ;
	back = (*map)->maps;
	map_cole = ft_strjoin(back, line);
	if (!map_cole)
		return (free_map_c(*map));
	(*map)->maps = map_cole;
	if (back)
		free(back);
}

int	creat_2darray(t_map_cub **map_c)
{
	if (!map_c || !(*map_c)->maps)
		return (ft_putstr_fd("ERROR\nNo map on file\n", 2), 0);
	(*map_c)->dmaps = ft_split((*map_c)->maps, '\n');
	if (!(*map_c)->dmaps)
		return (0);
	return (1);
}

int	find_player(t_map_cub **map)
{
	int		x;
	int		y;
	int		flag;

	x = 0;
	flag = 0;
	while ((*map)->dmaps[x])
	{
		y = 0;
		while ((*map)->dmaps[x][y])
		{
			if ((*map)->dmaps[x][y] == 'N' || (*map)->dmaps[x][y] == 'S'
				|| (*map)->dmaps[x][y] == 'W' || (*map)->dmaps[x][y] == 'E')
			{
				flag++;
				(*map)->player_pos->position_x = x + 0.5;
				(*map)->player_pos->position_y = y + 0.5;
			}
			y++;
		}
		x++;
	}
	if (flag != 1 || flag == 0)
		return (0);
	return (1);
}

float	ft_determinate_playerangle(t_map_cub **map)
{
	int	x;
	int	y;

	x = (int)(*map)->player_pos->position_x;
	y = (int)(*map)->player_pos->position_y;
	if ((*map)->dmaps[x][y] == 'N')
		return (M_PI / 2);
	if ((*map)->dmaps[x][y] == 'S')
		return (-M_PI / 2);
	if ((*map)->dmaps[x][y] == 'E')
		return (0);
	if ((*map)->dmaps[x][y] == 'W')
		return (M_PI);
	return (1);
}

int	handle_map(t_map_cub **map_c)
{
	if (!check_map_isvalid(*map_c))
		return (ft_putstr_fd("ERROR\nmap not valid!\n", 2), 0);
	if (!find_player(map_c))
		return (ft_putstr_fd("ERROR\nplayer not \
found or multi-player!\n", 2), 0);
	if (!check_close_map(*map_c))
		return (0);
	if (!check_map_bound((*map_c)->dmaps))
		return (ft_putstr_fd("ERROR\nmax bounds of map is 100*100\n", 2), 0);
	(*map_c)->player_pos->radius = 3;
	(*map_c)->player_pos->angle = ft_determinate_playerangle(map_c);
	(*map_c)->player_pos->forword_backword = 0;
	(*map_c)->player_pos->leftvu_rightvu = 0;
	(*map_c)->player_pos->rotate = 0;
	(*map_c)->player_pos->player_face = 0;
	(*map_c)->player_pos->player_fov = 0;
	return (1);
}
