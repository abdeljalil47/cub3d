/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:33:59 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 14:04:05 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

int	main(int ac, char *arg[])
{
	if (ac != 2)
		return (ft_putstr_fd("Error\n\tnot enough arguments\n", 2), -1);
	if (!check_map_extention(arg[1]))
		return (-1);
	return (0);
}
