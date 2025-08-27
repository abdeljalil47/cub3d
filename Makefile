CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast
MLXLIB = -lmlx -framework OpenGL -framework AppKit

SRC = parsing/pars_map.c cub3d.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	parsing/read_map.c init_data/init_data.c parsing/collecte_map.c parsing/check_coordonnes.c \
	parsing/check_close_map.c free_stuff/free_map.c free_stuff/free_map_c.c free_stuff/free_player.c \
	free_stuff/free_res.c rander_map/rander_map.c rander_map/put_texture.c rander_map/move_player.c \
	rays/cast_rays.c rays/wall_projection.c rander_map/check_top_move.c \
	rander_map/check_left_move.c parsing/check_map_coluction.c free_stuff/free_out.c rander_map/keymove.c\
	parsing/color_check.c parsing/handle_read_map.c rander_map/print_window_error.c rander_map/realasekey.c\
	rander_map/loopmain.c rander_map/checkmove.c rander_map/put_elements.c rays/load_textures.c \
	free_stuff/free_paths.c rays/halpfunction.c free_stuff/free_weapon.c rays/parse_textures.c \
	rays/get_texture_pixel.c rays/render_3d_helper.c rays/get_pixel_bounds.c rays/load_textures_helper.c \
	rays/castpart.c rander_map/playerdirec.c free_stuff/free_error.c rays/draw_hand.c

OBJ = $(SRC:.c=.o)
NAME = cub3d
LIB = libft/libft.a

GREEN = \033[1;32m
RED = \033[1;31m
CYAN = \033[1;36m
YELLOW = \033[1;33m
RESET = \033[0m

all: banner $(NAME)
	@echo "$(GREEN)✔ Build complete!$(RESET)"
	@echo "$(CYAN)🚀 Run ./cub3d map/map.cub to start the adventure!$(RESET)"

$(LIB):
	make -C libft

$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(MLXLIB) -o $@

%.o: %.c  header/cub3d.h libft/libft.h get_next_line/get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

banner:
	@echo ""
	@echo "$(CYAN)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢦⢟⣯⣶⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠞⣛⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡽⡿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⠘⠂⠀⠀⠀⠀⠀⠀⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⠀⠀⠀⠀⠀⠀⠀⡠⠶⠤⠔⣻⠻⣿⣿⣿⣿⣦⣤⣤⣤⠀⠀⠀⠀⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⠀⠀⠀⠀⠀⠀⢄⠀⠀⠀⠀⠜⣚⠻⠿⠟⠛⠛⠉⣹⣽⣷⡄⠀⠀⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⢀⠴⠤⡀⠀⡐⢰⡀⠀⠠⢀⢢⠁⠄⠀⠄⠀⣠⣾⣷⡀⣿⣇⠀⠀⠀⠀$(RESET)"
	@echo "$(CYAN)⣴⣿⣷⢿⣿⣶⢦⣺⣿⡇⠀⠀⠀⡸⣊⠙⠆⣠⣿⣿⣿⠷⣼⣿⠀⠀⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⠉⠉⠙⠛⣿⣗⣿⣻⣷⣶⣾⠚⠂⢚⢀⢀⣿⣿⣿⣿⣷⡺⣽⡇⠀⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⠀⠀⠀⠐⢿⣽⡟⢻⠿⣿⣿⣿⣶⣉⠈⣞⢽⣿⣿⡿⣿⢁⣸⣷⠀⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⠀⠀⠀⠱⣵⣿⣔⣷⣿⣿⣿⣿⣿⣿⣯⣾⣿⣿⣿⣧⣿⠛⣿⣿⡧⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⠀⠀⠀⠀⠀⠉⠉⠉⢹⣿⡿⠀⢼⣿⣿⣿⣿⣿⣿⣿⣿⢒⣿⣿⠁⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⠀⠀⠀⠀⠀⠀⠀⢸⡗⣻⡏⠀⢸⣿⣿⣿⣿⣿⢿⣿⣟⣿⣿⠁⠀⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⠀⠀⠀⠀⠀⠀⠀⣿⢓⠗⡇⠀⢸⣿⣿⣿⣿⣿⣯⣿⣿⣻⣷⠀⠀⠀⠀$(RESET)"
	@echo "$(CYAN)⠀⠀⠀⠀⠀⠀⠀⠀⣿⣼⢴⣽⡖⠻⠛⣿⠿⠿⠿⡿⣿⠀⠈⠻⢗⡄⣀⡤$(RESET)"
	@echo "$(CYAN)⠀⠀⠀⠀⠀⠀⠀⠀⠉⠜⢀⡵⠀⡀⣲⣋⡀⣀⣈⣧⣻⡀⠀⠀⠀⠉⠛⠇$(RESET)"
	@echo ""
	@echo "$(YELLOW)⚡ Created by: ahbilla & abdsebba ⚡$(RESET)"
	@echo ""

clean:
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re banner