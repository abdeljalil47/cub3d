/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_pixel_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:25:50 by ahbilla           #+#    #+#             */
/*   Updated: 2025/08/28 15:14:06 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

int	get_texture_pixel(t_texture *texture, int tex_x, int tex_y)
{
	int				bytes_per_pixel;
	int				index;
	unsigned char	*p;

	if (!texture || !texture->data)
		return (0);
	if (tex_x < 0 || tex_x >= texture->width
		|| tex_y < 0 || tex_y >= texture->height)
		return (0);
	bytes_per_pixel = texture->bpp / 8;
	index = (tex_y * texture->size_line) + (tex_x * bytes_per_pixel);
	if (bytes_per_pixel == 4)
		return (*(int *)(texture->data + index));
	else if (bytes_per_pixel == 3)
	{
		p = (unsigned char *)(texture->data + index);
		return ((p[0] << 16) | (p[1] << 8) | p[2]);
	}
	return (0);
}
