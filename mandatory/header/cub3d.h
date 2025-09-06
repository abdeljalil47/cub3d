/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:01:30 by ahbilla           #+#    #+#             */
/*   Updated: 2025/09/01 16:21:10 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# define MOVE_FAKE 10
# define MOVE_SPEED 4
# define TILE_SIZE 64
# define TILE_MINI 64
# define MINIMAP_SCALE 0.2
# define WALL_STRIP_WIDTH 1
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1200
# define FOV_ANGLE 1.0471975512
# define ROTATION_SPEED 0.05235987756
# define NUM_RAYS WINDOW_WIDTH

# define KEY_KNIFE 14
# define KEY_RELEASE_1 259
# define KEY_RELEASE_2 260
# define KEY_ESC 53
# define KEY_S 1
# define KEY_W 13
# define KEY_D 2
# define KEY_A 0
# define ARROW_LEFT 123
# define ARROW_RIGHT 124

typedef struct s_player	t_player;
typedef struct s_data	t_data;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		tex_x;
}	t_ray;

typedef struct s_map_valid
{
	char				*type;
	char				*path;
	char				*color;
	bool				coordonne;
	int					color_rgb;
	struct s_map_valid	*next;
}	t_map_valid;

typedef struct s_map_cub
{
	char		*maps;
	char		**dmaps;
	t_player	*player_pos;
}	t_map_cub;

typedef struct s_player
{
	float	position_x;
	float	position_y;
	int		radius;
	float	angle;
	int		forword_backword;
	int		leftvu_rightvu;
	int		rotate;
	int		player_fov;
	int		player_face;
}	t_player;

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		*datas;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_texture_path
{
	char	*wall_no;
	char	*wall_so;
	char	*wall_we;
	char	*wall_ea;
}	t_texture_path;

typedef struct s_render
{
	float	wall_height;
	int		top_pixel;
	int		bottom_pixel;
	float	step;
	float	tex_pos;
	int		y;
	int		x;
}	t_render;

typedef struct s_table
{
	void			*mlx;
	void			*mlx_win;
	void			*wall_img;
	void			*player;
	int				width;
	int				height;
	t_texture_path	*tex_path;
	int				ciel;
	int				floor;
	void			*img;
	char			*img_data;
	int				bpp;
	int				size_line;
	int				endian;
	float			last_time;
	t_texture		textures[5];
	int				scaled_width;
	int				scaled_height;
	int				start_x;
	int				start_y;
	int				current_frame;
	int				anim_counter;
	t_map_cub		*map_stru;
	t_map_valid		*map_ele;
	t_player		*player_coor;
	t_data			*data;
	t_ray			rays[NUM_RAYS];
	int				flag;
}	t_table;

typedef struct s_data
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
}	t_data;

typedef struct s_horz_data
{
	float	player_x;
	float	player_y;
	float	x_step;
	float	y_step;
	float	next_x;
	float	next_y;
	int		facing_up;
}	t_horz_data;

typedef struct s_vert_data
{
	float	player_x;
	float	player_y;
	float	x_step;
	float	y_step;
	float	next_x;
	float	next_y;
	int		facing_left;
}	t_vert_data;

typedef struct s_hit
{
	float	x;
	float	y;
	float	dist;
}	t_hit;

int			check_map_extention(char *av);
int			read_map(char *av);
int			check_type(char **res, int flag);
int			check_prev(int j, char *tmp, char *prev, char *next);
int			check_map_bound(char **map);
int			ischaracters(char *line);
int			close_window(void *param);
void		cast_all_rays(t_table *table);
int			relase_keycode(int keycode, t_table *data);
int			keycode(int key, void *param);
int			count_height(char **line);
int			find_map_width(char **dmaps);
int			mainloop(void *param);
int			get_inverse_color(int color, char type);
void		normalize_angle(float *angle);
void		player_coordonneup(t_table **data);
int			has_wall_at(t_table *table, float x, float y);
int			check_top_move(t_table *table, float x, float y);
int			check_bottom_move(t_table *table, float x, float y);
int			check_left_move(t_table *table, float x, float y);
int			check_right_move(t_table *table, float x, float y);
void		put_pixel(t_table *table, int x, int y, int color);
int			cast_rays(t_table *table, float ray_angle, int columnid);
void		print_window_error(void);
void		free_res(char **res);
void		clean_beforeout(t_table **ptable);
int			get_texture_pixel(t_texture *texture, int tex_x, int tex_y);
void		render_3d_projection(t_table *table);
void		find_texture_wall_angle(t_table *table);
int			load_textures(t_table *table);
char		*ft_my_strcat(char *dest, int num, char *src);
void		find_ceiling_floor(t_table *table, int *c, int *f);
void		get_pixel_bounds(float wall_height,
				int *top_pixel, int *bottom_pixel);
void		validate_table(t_table *table);
float		calculate_wall_height(t_ray *ray, float player_angle,
				float dist_project);
t_texture	*select_vertical_texture(t_ray *ray, t_table *table, int *flip_x);
t_texture	*select_horizontal_texture(t_ray *ray, t_table *table, int *flip_x);
t_texture	*select_texture(t_ray *ray,
				t_table *table, int *flip_x);
int			rander_map(t_map_valid **map_element, t_map_cub **map_structure,
				t_player **player_cor);
float		cast_horz_intersection(t_table *table,
				float ray_angle, float *hit_x, float *hit_y);
int			check_type_cordonnes(t_map_valid *lst);
int			handle_cordonnes(char *line, t_map_valid **map);
int			is_empty_line(char *line);
void		collecte_map(char *line, t_map_cub **map);
int			has_wall_at_for_ray(t_table *table, float x, float y);
void		free_onerror(t_table *table, int flag);
int			check_element(char c);
void		init_map(t_map_valid **map, char **value);
int			check_close_map(t_map_cub *map);
int			check_map_isvalid(t_map_cub *map_c);
int			creat_2darray(t_map_cub **map_c);
int			ft_handle_path(t_map_valid *val);
int			handle_map(t_map_cub **map_c);
int			ft_handle_color(t_map_valid *map);
int			check_texture_extention(t_map_valid *av);
int			read_lines(char *av, t_map_valid **map, t_map_cub **map_c, int i);
void		free_player(t_player *player);
void		free_map_c(t_map_cub *map);
void		free_map(t_map_valid **maps);
void		clearwindow(t_table *table);

#endif