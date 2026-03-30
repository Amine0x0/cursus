CC = cc
CFLAGS = -Wall -Wextra -Werror -I./mlx
LIBFT_DIR = ./libft
MLX_DIR = /home/amabbadi/.local/lib/mlx
SRC_DIR = ./srcs
GNL_DIR = ./GNL
INCLUDES1 = ./libft/libft.h
INCLUDES2 = ./GNL/get_next_line.h 

SRC_FILES = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/draw.c \
	$(SRC_DIR)/events.c \
	$(SRC_DIR)/file_checks.c \
	$(SRC_DIR)/map.c \
	$(SRC_DIR)/allocators.c\
	$(SRC_DIR)/misc1.c\
	$(SRC_DIR)/misc2.c\
	$(SRC_DIR)/projections.c\
	$(SRC_DIR)/controls.c \
	$(SRC_DIR)/color.c \
	$(SRC_DIR)/draw_utils.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/process.c \
	$(SRC_DIR)/rotation.c \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c \
	$(LIBFT_DIR)/ft_atoi.c \
	$(LIBFT_DIR)/ft_bzero.c \
	$(LIBFT_DIR)/ft_calloc.c \
	$(LIBFT_DIR)/ft_isalnum.c \
	$(LIBFT_DIR)/ft_isalpha.c \
	$(LIBFT_DIR)/ft_isascii.c \
	$(LIBFT_DIR)/ft_isdigit.c \
	$(LIBFT_DIR)/ft_isprint.c \
	$(LIBFT_DIR)/ft_itoa.c \
	$(LIBFT_DIR)/ft_memchr.c \
	$(LIBFT_DIR)/ft_memcmp.c \
	$(LIBFT_DIR)/ft_memcpy.c \
	$(LIBFT_DIR)/ft_memmove.c \
	$(LIBFT_DIR)/ft_memset.c \
	$(LIBFT_DIR)/ft_putchar_fd.c \
	$(LIBFT_DIR)/ft_putendl_fd.c \
	$(LIBFT_DIR)/ft_putnbr_fd.c \
	$(LIBFT_DIR)/ft_putstr_fd.c \
	$(LIBFT_DIR)/ft_split.c \
	$(LIBFT_DIR)/ft_strchr.c \
	$(LIBFT_DIR)/ft_strdup.c \
	$(LIBFT_DIR)/ft_striteri.c \
	$(LIBFT_DIR)/ft_strjoin.c \
	$(LIBFT_DIR)/ft_strlcat.c \
	$(LIBFT_DIR)/ft_strlcpy.c \
	$(LIBFT_DIR)/ft_strlen.c \
	$(LIBFT_DIR)/ft_strmapi.c \
	$(LIBFT_DIR)/ft_strncmp.c \
	$(LIBFT_DIR)/ft_strnstr.c \
	$(LIBFT_DIR)/ft_strrchr.c \
	$(LIBFT_DIR)/ft_strtrim.c \
	$(LIBFT_DIR)/ft_substr.c \
	$(LIBFT_DIR)/ft_tolower.c \
	$(LIBFT_DIR)/ft_toupper.c \

OBJ_FILES = $(SRC_FILES:.c=.o)
NAME = fdf

all: $(NAME)

$(NAME): $(OBJ_FILES) $(INCLUDES1) $(INCLUDES2)
	$(CC) $(OBJ_FILES) -o $(NAME) -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

%.o: %.c $(INCLUDES1) $(INCLUDES2)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re