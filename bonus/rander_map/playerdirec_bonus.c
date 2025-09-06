/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerdirec_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:09:11 by abdsebba          #+#    #+#             */
/*   Updated: 2025/09/02 15:59:05 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

int	get_inverse_color(int color, char type)
{
	int	r;
	int	g;
	int	b;
	int	temp;

	r = 0;
	g = 0;
	b = 0;
	if (type == 'M')
	{
		r = 255 - ((color >> 16) & 0xFF);
		g = 255 - ((color >> 8) & 0xFF);
		b = 255 - (color & 0xFF);
	}
	else if (type == 'P')
	{
		temp = r;
		r = (b + 100) % 256;
		g = (g + 60) % 256;
		b = (temp + 30) % 256;
	}
	return ((r << 16) | (g << 8) | b);
}
