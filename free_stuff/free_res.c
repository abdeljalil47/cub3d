#include "../header/cub3d.h"

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
