#ifndef CUP_H
#define CUP_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

#define MINIMAP_SIZE 160  // Fixed 200x200 minimap
#define MINIMAP_CENTER (MINIMAP_SIZE / 2)  // Center at (100, 100)
#define MOVE_FAKE 10
#define MOVE_SPEED 15
#define TILE_SIZE 64
#define TILE_MINI 64
#define MINIMAP_SCALE 0.2
#define WALL_STRIP_WIDTH 1  //change the distance between the rays
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1200
#define FOV_ANGLE (M_PI / 3)
#define NUM_RAYS (WINDOW_WIDTH / WALL_STRIP_WIDTH)
#define ROTATION_SPEED (6 * (M_PI / 180))// +more for rotation speed (10 * (M_PI / 180))

typedef struct player player;
typedef struct s_data t_data;

typedef struct s_ray
{
    float	rayAngle;
    float	wallHitX;
    float	wallHitY;
    float	distance;
    int		wasHitVertical;
	int		hittype; // 0 = none, 1 is wall, 2 is door
} t_ray;


#define HAND_FRAMES_KNIFE 23
#define HAND_FRAMES_KNIFE_MV 30
#define HAND_ANIM_SPEED 0.2

typedef struct map_valid
{
	char	*type;
	char	*path;
	char	*color;
	bool	coordonne;
	int		color_rgb;
	struct map_valid	*next;
} map_valid;

typedef struct map_cub
{
	char	*maps;
	char	**dmaps;
	player	*player_pos;
} map_cub;

typedef struct player
{
	float	position_x;
	float	position_y;
	int		radius;
	float	angle;
	int		forword_backword;    // 1 top; -1 bottom
	int		leftvu_rightvu;  // -1 left; 1 right
	int		rotate;
	int		player_fov;  // 1 left; -1 right;
	int		player_face;  // 1 top; -1 bottom;
} player;
typedef struct s_texture
{
	void *img;
	char *data;
	int bpp;
	int size_line;
	int endian;
	int width;
	int height;
} t_texture;
typedef struct s_texture_path
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
}t_texture_path;
typedef struct s_hand_anim
{
	char *hand_paths[HAND_FRAMES_KNIFE];
	char *hand_paths_mv[HAND_FRAMES_KNIFE_MV];
    int current_frame;
    int anim_counter;
	bool flag;
	bool finished;
	int loaded_knife;
	int loaded_knife_mv;
} t_hand_anim;

typedef struct s_taple
{
	void		*mlx;
	void		*mlx_win;
	void		*wall_img;
	void		*player;
	int			width;
	int			height;
	t_texture	wall_texture;
	t_texture_path tex_path;
	void *img;
    char *img_data;
    int bpp;
    int size_line;
    int endian;
	int				open_door;
	t_texture textures[5];
	t_texture   hand_frames[5];
	t_hand_anim hand_anim;
	    int current_frame;
    int anim_counter;
	bool door_exist;
	map_cub		*map_stru;
	map_valid	*map_ele;
	player		*player_coor;
	t_data		*data;
	t_ray		rays[NUM_RAYS];
	int flag;
} t_table;

int		check_map_extention(char *av);
int		check_texture_extention(map_valid *texture);
int		read_map(char *av);
void	init_map(map_valid **map, char **value);
char	ft_putnbr_base(long nbr, const char *base);
void    collecte_map(char *line, map_cub **map);
int		creat_2darray(map_cub **map_c);
int		handle_map(map_cub **map_c);
int		check_close_map(map_cub *map);
int check_type(char **res, int flag);

int count_height(char **line);
int find_map_width(char **dmaps);

int	rander_map(map_valid **map_element, map_cub **map_structure, player **player_coor);
int	put_texture(t_table *table);
void normalize_angle(float *angle);
void	player_coordonneup(t_table **data);
int	ft_move_check(t_table *table, float x, float y);
int ft_put_player(t_table **data);
void normalize_angle(float *angle);

int open_door(t_table *data);

int	check_top_move(t_table *table, float x, float y);
int	check_bottom_move(t_table *table, float x, float y);
int	check_left_move(t_table *table, float x, float y);
int	check_right_move(t_table *table, float x, float y);

void draw_line(t_table *table, int x0, int y0, int x1, int y1, int color);
void put_pixel(t_table *table, int x, int y, int color);

int	cast_rays(t_table *table, float ray_angle, int columnid);
int	wall_projection(t_table *table);

int weapon(t_table *table, char *type_mv);

int	count_height(char **line);

void	free_res(char **res);
void	free_map(map_valid **map);
void	free_map_c(map_cub *map);
void	free_player(player *player);

int		find_ceiling_floor(t_table *table, char type);

#endif