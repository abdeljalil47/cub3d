CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast -fsanitize=address 
MLXLIB = -lmlx -framework OpenGL -framework AppKit

SRC = mandatory/parsing/pars_map.c mandatory/cub3d.c mandatory/get_next_line/get_next_line.c mandatory/get_next_line/get_next_line_utils.c \
	mandatory/parsing/read_map.c mandatory/init_data/init_data.c mandatory/parsing/collecte_map.c mandatory/parsing/check_coordonnes.c \
	mandatory/parsing/check_close_map.c mandatory/free_stuff/free_map.c mandatory/free_stuff/free_map_c.c mandatory/free_stuff/free_player.c \
	mandatory/free_stuff/free_res.c mandatory/rander_map/rander_map.c mandatory/rander_map/move_player.c \
	mandatory/rays/cast_rays.c mandatory/rays/wall_projection.c mandatory/rander_map/check_top_move.c \
	mandatory/rander_map/check_left_move.c mandatory/parsing/check_map_coluction.c mandatory/free_stuff/free_out.c mandatory/rander_map/keymove.c\
	mandatory/parsing/color_check.c mandatory/parsing/handle_read_map.c mandatory/rander_map/print_window_error.c mandatory/rander_map/realasekey.c\
	mandatory/rander_map/loopmain.c mandatory/rander_map/checkmove.c \
	mandatory/free_stuff/free_paths.c mandatory/rays/halpfunction.c mandatory/rays/parse_textures.c \
	mandatory/rays/get_texture_pixel.c mandatory/rays/render_3d_helper.c mandatory/rays/get_pixel_bounds.c mandatory/rays/load_textures_helper.c \
	mandatory/rays/castpart.c

BONUS_SRC = bonus/parsing/pars_map_bonus.c bonus/cub3d_bonus.c bonus/get_next_line/get_next_line_bonus.c bonus/get_next_line/get_next_line_utils_bonus.c \
	bonus/parsing/read_map_bonus.c bonus/init_data/init_data_bonus.c bonus/parsing/collecte_map_bonus.c bonus/parsing/check_coordonnes_bonus.c \
	bonus/parsing/check_close_map_bonus.c bonus/free_stuff/free_map_bonus.c bonus/free_stuff/free_map_c_bonus.c bonus/free_stuff/free_player_bonus.c \
	bonus/free_stuff/free_res_bonus.c bonus/rander_map/rander_map_bonus.c bonus/rander_map/put_texture_bonus.c bonus/rander_map/move_player_bonus.c \
	bonus/rays/cast_rays_bonus.c bonus/rays/wall_projection_bonus.c bonus/rander_map/check_top_move_bonus.c \
	bonus/rander_map/check_left_move_bonus.c bonus/parsing/check_map_coluction_bonus.c bonus/free_stuff/free_out_bonus.c bonus/rander_map/keymove_bonus.c \
	bonus/parsing/color_check_bonus.c bonus/parsing/handle_read_map_bonus.c bonus/rander_map/print_window_error_bonus.c bonus/rander_map/realasekey_bonus.c \
	bonus/rander_map/loopmain_bonus.c bonus/rander_map/checkmove_bonus.c bonus/rander_map/put_elements_bonus.c bonus/rays/load_textures_bonus.c \
	bonus/free_stuff/free_paths_bonus.c bonus/rays/halpfunction_bonus.c bonus/free_stuff/free_weapon_bonus.c bonus/rays/parse_textures_bonus.c \
	bonus/rays/get_texture_pixel_bonus.c bonus/rays/render_3d_helper_bonus.c bonus/rays/get_pixel_bounds_bonus.c bonus/rays/load_textures_helper_bonus.c \
	bonus/rays/castpart_bonus.c bonus/rander_map/playerdirec_bonus.c bonus/free_stuff/free_error_bonus.c bonus/rays/draw_hand_bonus.c


OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

NAME = cub3D
NAME_BONUS = cub3D_bonus

LIB_bonus = bonus/libft/libft.a
LIB_manda = mandatory/libft/libft.a

GREEN = \033[1;32m
RED = \033[1;31m
CYAN = \033[1;36m
YELLOW = \033[1;33m
RESET = \033[0m

all: banner $(NAME)
	@echo "$(GREEN)✔ Build Mandatory Complete!$(RESET)"
	@echo "$(CYAN)🚀 Run ./cub3d map/map.cub to start the adventure!$(RESET)"

bonus: banner $(NAME_BONUS)
	@echo "$(GREEN)✔ Build Bonus Complete!$(RESET)"
	@echo "$(CYAN)🚀 Run ./cub3d_bonus map/map.cub to start the adventure!$(RESET)"

$(NAME):  $(OBJ) 
	make -C mandatory/libft
	$(CC) $(CFLAGS) $(OBJ) $(LIB_manda) $(MLXLIB) -o $@

mandatory/%.o: mandatory/%.c mandatory/header/cub3d.h mandatory/libft/libft.h mandatory/get_next_line/get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_BONUS): $(LIB_bonus) $(BONUS_OBJ)
	make -C bonus/libft
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIB_bonus) $(MLXLIB) -o $@

bonus/%.o: bonus/%.c bonus/header/cub3d_bonus.h bonus/libft/libft.h bonus/get_next_line/get_next_line.h
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
	rm -f $(BONUS_OBJ)

fclean: clean
	make fclean -C mandatory/libft
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re banner