/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:33:10 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/27 17:33:11 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	free_paths(char **paths, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(paths[i]);
		i++;
	}
}
