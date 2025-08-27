/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   halpfunction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:05:33 by ahbilla           #+#    #+#             */
/*   Updated: 2025/08/27 17:08:27 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

static int	ft_intlen(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_putnbr_str(int n, char *res, int *i)
{
	int	len;
	int	j;
	int	tmp;

	len = ft_intlen(n);
	tmp = n;
	j = len - 1;
	while (j >= 0)
	{
		res[*i + j] = (tmp % 10) + '0';
		tmp /= 10;
		j--;
	}
	*i += len;
}

char	*ft_my_strcat(char *dest, int num, char *src)
{
	int		i;
	int		dest_len;
	int		src_len;
	char	*res;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	res = malloc(dest_len + ft_intlen(num) + src_len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < dest_len)
	{
		res[i] = dest[i];
		i++;
	}
	ft_putnbr_str(num, res, &i);
	while (*src)
		res[i++] = *src++;
	res[i] = '\0';
	return (res);
}
