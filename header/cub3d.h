#ifndef CUP_H
#define CUP_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

typedef struct player player;

typedef struct map_valid
{
	char *type;
	char *path;
	char *color;
	bool coordonne;
	int color_rgb;
	struct map_valid *next;
} map_valid;

typedef struct map_cub
{
	char *maps;
	char **dmaps;
	player *player_pos;
} map_cub;

typedef struct player
{
	int position_x;
	int position_y;
} player;

int check_map_extention(char *av);
int check_texture_extention(map_valid *texture);
int read_map(char *av);
void init_map(map_valid **map, char **value);
char	ft_putnbr_base(long nbr, const char *base);
void    collecte_map(char *line, map_cub **map);
int creat_2darray(map_cub **map_c);
int handle_map(map_cub **map_c);
int	check_close_map(map_cub *map);
int check_type(char **res, int flag);

void	free_res(char **res);
void	free_map(map_valid **map);
void	free_map_c(map_cub *map);
void	free_player(player *player);


#endif