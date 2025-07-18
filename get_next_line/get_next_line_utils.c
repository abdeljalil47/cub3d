/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:04:43 by abdsebba          #+#    #+#             */
/*   Updated: 2025/07/15 20:57:06 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lenght;

	i = 0;
	lenght = ft_strlen(src);
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (lenght);
}

char	*ft_strdup(const char *s)
{
	char	*array;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	array = (char *)malloc((len + 1) * sizeof(char));
	if (array == NULL)
		return (NULL);
	while (s[i])
	{
		array[i] = s[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*array;

	if (s == NULL && start == 0)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		array = (char *)malloc(sizeof(char));
		if (array == NULL)
			return (NULL);
		if (array != NULL)
			array[0] = '\0';
		return (array);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	array = (char *)malloc((len + 1) * sizeof(char));
	if (array == NULL)
		return (NULL);
	ft_strlcpy(array, s + start, len + 1);
	return (array);
}
