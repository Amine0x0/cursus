NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = src/pipex.c src/misc1.c src/misc2.c src/toolkit.c ft_printf/printf.c  ft_printf/non_hexautils.c ft_printf/hexa_utils.c
OBJ = $(SRC:.c=.o)
HEADER = includes/pipex.h
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
