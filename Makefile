CC=cc
CFLAGS=-Wall -Wextra -Werror
SRC=parsing/pars_map.c cub3d.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c parsing/read_map.c\
	init_data/init_data.c parsing/putnbr_base.c parsing/collecte_map.c parsing/check_close_map.c\
	free_stuff/free_map.c free_stuff/free_map_c.c free_stuff/free_player.c free_stuff/free_res.c

OBJ=$(SRC:.c=.o)
NAME=cub3d
LIB=libft/libft.a


all: $(NAME)

$(NAME): $(OBJ)
#make all -C libft -g -fsanitize=address
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

%.o:%.c header/cub3d.h libft/libft.h get_next_line/get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
#make clean -C libft
	rm $(OBJ)

fclean: clean
#make fclean -C libft
	rm $(NAME)

re: fclean all