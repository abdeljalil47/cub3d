#ifndef CUP_H
#define CUP_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

#define move_speed 0.2

typedef struct player player;
typedef struct s_data t_data;

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
	int	radius;
	double angle;
	float rotation_speed;
	int	forword_backword;    // 1 for; -1 back
	int	leftword_rightword;  // 1 lefr; -1 right
} player;

typedef struct s_taple
{
	void		*mlx;
	void		*mlx_win;
	void		*wall_img;
	void		*player;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	map_cub		*map_stru;
	map_valid	*map_ele;
	player		*player_coor;
	t_data		*data;
} t_table;

typedef struct s_data
{
	char	*frames[45];
	void	*mlx_frame[45];
	int		width;
	int		height;
	long	current_time;
	int		frame_id;
	void *img;																							
}	t_data;


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

long	get_time();

int	rander_map(map_valid **map_element, map_cub **map_structure, player **player_coor);
int	put_texture(t_table *table);
void	player_coordonneup(t_table **data);
int	get_path_frame(t_table **param);
int	player_effect(void *param);

void	free_res(char **res);
void	free_map(map_valid **map);
void	free_map_c(map_cub *map);
void	free_player(player *player);


#endif