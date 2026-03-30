NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror 
MLX_DIR = $(HOME)/mlx
MANDATORY_DIR = src/mandatory
BONUS_DIR = src/bonus

MANDATORY_SRC = $(MANDATORY_DIR)/main.c \
				$(MANDATORY_DIR)/cleanup/cleanup.c \
				$(MANDATORY_DIR)/cleanup/cleanup_helpers.c \
				$(MANDATORY_DIR)/terminal/close_handler.c \
				$(MANDATORY_DIR)/terminal/errors.c \
				$(MANDATORY_DIR)/terminal/logging.c \
				$(MANDATORY_DIR)/drawing/draw.c \
				$(MANDATORY_DIR)/drawing/draw_utils.c \
				$(MANDATORY_DIR)/drawing/draw_helpers.c \
				$(MANDATORY_DIR)/drawing/textures.c \
				$(MANDATORY_DIR)/utils/ft_atoi.c \
				$(MANDATORY_DIR)/utils/init.c \
				$(MANDATORY_DIR)/utils/ft_split.c \
				$(MANDATORY_DIR)/utils/ft_strcmp.c \
				$(MANDATORY_DIR)/utils/ft_memset.c \
				$(MANDATORY_DIR)/utils/game_init_helpers.c \
				$(MANDATORY_DIR)/utils/game_init_helpers2.c \
				$(MANDATORY_DIR)/utils/load_map.c \
				$(MANDATORY_DIR)/utils/GNL/get_next_line.c \
				$(MANDATORY_DIR)/utils/GNL/get_next_line_utils.c \
				$(MANDATORY_DIR)/movement/movement.c \
				$(MANDATORY_DIR)/movement/movement_helpers.c \
				$(MANDATORY_DIR)/parse/handle_rgb.c \
				$(MANDATORY_DIR)/parse/handle_textures.c \
				$(MANDATORY_DIR)/parse/map_check_firstlines.c \
				$(MANDATORY_DIR)/parse/map_check.c \
				$(MANDATORY_DIR)/parse/parse_map.c \
				$(MANDATORY_DIR)/parse/mapcheck_helper.c \
				$(MANDATORY_DIR)/parse/padmap.c\
				$(MANDATORY_DIR)/parse/flodfill.c \
				$(MANDATORY_DIR)/drawing/drawing_utils.c \
				$(MANDATORY_DIR)/parse/flood_fill_utils.c \

BONUS_SRC = $(BONUS_DIR)/main_bonus.c \
			$(BONUS_DIR)/utils/main_helpers_bonus.c \
			$(BONUS_DIR)/cleanup/cleanup_bonus.c \
			$(BONUS_DIR)/cleanup/cleanup_helpers_bonus.c \
			$(BONUS_DIR)/drawing/draw_bonus.c \
			$(BONUS_DIR)/drawing/draw_helpers_bonus.c \
			$(BONUS_DIR)/drawing/draw_helpers2_bonus.c \
			$(BONUS_DIR)/drawing/draw_utils_bonus.c \
			$(BONUS_DIR)/drawing/textures_bonus.c \
			$(BONUS_DIR)/movement/movement_bonus.c \
			$(BONUS_DIR)/movement/movement_helpers_bonus.c \
			$(BONUS_DIR)/movement/movement_utils_bonus.c \
			$(BONUS_DIR)/menu/menu_bonus.c \
			$(BONUS_DIR)/menu/menu_helpers_bonus.c \
			$(BONUS_DIR)/menu/menu_simulation_bonus.c \
			$(BONUS_DIR)/menu/menu_utils_bonus.c \
			$(BONUS_DIR)/sprite/sprite_bonus.c \
			$(BONUS_DIR)/sprite/sprite_helpers_bonus.c \
			$(BONUS_DIR)/terminal/close_handler_bonus.c \
			$(BONUS_DIR)/terminal/errors_bonus.c \
			$(BONUS_DIR)/terminal/logging_bonus.c \
			$(BONUS_DIR)/utils/ft_atoi_bonus.c \
			$(BONUS_DIR)/utils/ft_split_bonus.c \
			$(BONUS_DIR)/utils/ft_strcmp_bonus.c \
			$(BONUS_DIR)/utils/ft_memset_bonus.c \
			$(BONUS_DIR)/utils/init_bonus.c \
			$(BONUS_DIR)/utils/game_init_helpers_bonus.c \
			$(BONUS_DIR)/utils/game_init_helpers2_bonus.c \
			$(BONUS_DIR)/utils/load_map_bonus.c \
			$(BONUS_DIR)/utils/GNL/get_next_line.c \
			$(BONUS_DIR)/utils/GNL/get_next_line_utils.c \
			$(BONUS_DIR)/parse/handle_rgb_bonus.c \
			$(BONUS_DIR)/parse/handle_textures_bonus.c \
			$(BONUS_DIR)/parse/map_check_firstlines_bonus.c \
			$(BONUS_DIR)/parse/map_check_bonus.c \
			$(BONUS_DIR)/parse/parse_map_bonus.c \
			$(BONUS_DIR)/parse/mapcheck_helper_bonus.c \
			$(BONUS_DIR)/parse/padmap_bonus.c\
			$(BONUS_DIR)/parse/flodfill_bonus.c \
			$(BONUS_DIR)/parse/flood_fill_utils_bonus.c \
			$(BONUS_DIR)/drawing/drawing_utils_bonus.c \

MANDATORY_OBJ = $(MANDATORY_SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(MANDATORY_OBJ) include/cub3D.h $(MLX_DIR)/libmlx_Linux.a
	$(CC) $(CFLAGS) -o $(NAME) $(MANDATORY_OBJ) -I$(MLX_DIR) -Iinclude $(MLX_DIR)/libmlx_Linux.a -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OBJ) include/cub3D_bonus.h $(MLX_DIR)/libmlx_Linux.a
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(BONUS_OBJ) -I$(MLX_DIR) -Iinclude $(MLX_DIR)/libmlx_Linux.a -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

%.o: %.c include/cub3D.h include/cub3D_bonus.h
	$(CC) $(CFLAGS) -c $< -I$(MLX_DIR) -I$(MANDATORY_DIR)/utils/GNL -I$(BONUS_DIR)/utils/GNL -Iinclude -o $@

$(MLX_DIR)/libmlx_Linux.a:
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(MANDATORY_OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
