/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_res_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:33:05 by abdsebba          #+#    #+#             */
/*   Updated: 2025/08/28 15:09:01 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d_bonus.h"

void	free_res(char **res)
{
	int	i;

	if (!res)
		return ;
	i = -1;
	while (res[++i])
	{
		if (res[i])
			free(res[i]);
	}
	free(res);
}
