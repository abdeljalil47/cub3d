/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realasekey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:08:48 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/27 17:08:49 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	relase_keycode(int keycode, t_table *data)
{
	t_player	*player_data;

	player_data = data->player_coor;
	if (keycode == 259 || keycode == 260)
	{
		player_data->forword_backword = 0;
		player_data->leftvu_rightvu = 0;
		player_data->rotate = 0;
		return (0);
	}
	if (keycode == 13 || keycode == 1)
		player_data->forword_backword = 0;
	if (keycode == 0 || keycode == 2)
		player_data->leftvu_rightvu = 0;
	if (keycode == 123 || keycode == 124)
		player_data->rotate = 0;
	return (0);
}
