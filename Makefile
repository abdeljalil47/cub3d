CC = cc
CFLAGS = -Wall -Wextra -Werror -ofast
MLXLIB = -lmlx -framework OpenGL -framework AppKit

SRC = parsing/pars_map.c cub3d.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	parsing/read_map.c init_data/init_data.c parsing/collecte_map.c \
	parsing/check_close_map.c free_stuff/free_map.c free_stuff/free_map_c.c free_stuff/free_player.c \
	free_stuff/free_res.c rander_map/rander_map.c rander_map/put_texture.c rander_map/move_player.c \
	rander_map/player_effect.c rays/cast_rays.c rays/wall_projection.c rander_map/check_top_move.c \
	rander_map/check_left_move.c rander_map/open_door.c

OBJ = $(SRC:.c=.o)
NAME = cub3d
LIB = libft/libft.a
LIBMLX=minilibx_opengl_20191021/libmlx.a

all: $(NAME)

$(LIB):
	make -C libft

$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(MLXLIB) -o $@

%.o: %.c header/cub3d.h libft/libft.h get_next_line/get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re