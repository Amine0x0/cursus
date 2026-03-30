SRCS = printf.c hexa_utils.c non_hexautils.c
CC = cc
HEADER = ft_printf.h
FLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
OBJS = $(SRCS:.c=.o)
all: $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean
