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

#define MINIMAP_SIZE 160  // Fixed 200x200 minimap
#define MINIMAP_CENTER (MINIMAP_SIZE / 2)  // Center at (100, 100)

#define MOVE_FAKE 0.1
#define MOVE_SPEED 0.2
#define TILE_SIZE 32
#define MINIMAP_SCALE 0.2
#define WALL_STRIP_WIDTH 1  //change the distance between the rays
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1200
#define FOV_ANGLE (M_PI / 3)
#define NUM_RAYS (WINDOW_WIDTH / WALL_STRIP_WIDTH)
#define ROTATION_SPEED 9 * (M_PI / 180)// +more for rotation speed (10 * (M_PI / 180))

typedef struct player player;
typedef struct s_data t_data;

typedef struct s_ray {
    double rayAngle;
    double wallHitX;
    double wallHitY;
    double distance;
    int wasHitVertical;
} t_ray;


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
	double position_x;
	double position_y;
	int	radius;
	double angle;
	int	forword_backword;    // 1 top; -1 bottom
	int	leftvu_rightvu;  // -1 left; 1 right
	int rotate;
	int	player_fov;  // 1 left; -1 right;
	int	player_face;  // 1 top; -1 bottom;
} player;

typedef struct s_taple
{
	void		*mlx;
	void		*mlx_win;
	void		*wall_img;
	void		*player;
	int			width;
	int			height;
	void *img; // Add this
    char *img_data; // Add this
    int bpp; // Add this
    int size_line; // Add this
    int endian; // Add this
	double last_time;
	map_cub		*map_stru;
	map_valid	*map_ele;
	player		*player_coor;
	t_data		*data;
	t_ray		rays[NUM_RAYS];
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
void normalize_angle(double *angle);
void	player_coordonneup(t_table **data);
int	ft_move_check(t_table *table, double x, double y);
int	get_path_frame(t_table **param);
int	player_effect(void *param);
int ft_put_player(t_table **data);
void normalize_angle(double *angle);

int	check_top_move(t_table *table, double x, double y);
int	check_bottom_move(t_table *table, double x, double y);
int	check_left_move(t_table *table, double x, double y);
int	check_right_move(t_table *table, double x, double y);

void draw_line(t_table *table, int x0, int y0, int x1, int y1, int color);
void put_pixel(t_table *table, int x, int y, int color);

int	cast_rays(t_table *table, double ray_angle, int columnid);
int	wall_projection(t_table *table);

void	free_res(char **res);
void	free_map(map_valid **map);
void	free_map_c(map_cub *map);
void	free_player(player *player);


#endif