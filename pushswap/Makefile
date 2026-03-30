NAME = push_swap
CC = cc
CFLAGS	= -Wall -Wextra -Werror

SRCS = src/pushswap.c src/push_op.c src/rot_op.c src/sort.c \
			  src/stack_stat.c src/swap_op.c src/utils.c src/index.c \
			  src/reroll.c src/rev_rot_op.c src/sort_fast.c \
			  src/check_parse.c src/misc1.c src/misc2.c

OBJS	= $(SRCS:.c=.o)
HEADER	= ./push_swap.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
