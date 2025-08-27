/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:33:07 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/27 17:33:08 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	free_player(t_player *player)
{
	if (player)
	{
		free(player);
		player = NULL;
	}
}
