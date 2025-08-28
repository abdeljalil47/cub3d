/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_bounds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:31:38 by ahbilla           #+#    #+#             */
/*   Updated: 2025/08/27 19:04:56 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

void	get_pixel_bounds(float wall_height, int *top_pixel, int *bottom_pixel)
{
	*top_pixel = (int)(WINDOW_HEIGHT / 2 - wall_height / 2);
	*bottom_pixel = (int)(WINDOW_HEIGHT / 2 + wall_height / 2);
	if (*top_pixel < 0)
		*top_pixel = 0;
	if (*bottom_pixel >= WINDOW_HEIGHT)
		*bottom_pixel = WINDOW_HEIGHT - 1;
}
