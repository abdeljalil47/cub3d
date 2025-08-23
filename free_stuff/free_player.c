#include "../header/cub3d.h"

void	free_player(player *player)
{
	
	if (player)
	{
		free(player);
		player = NULL;
	}
}
