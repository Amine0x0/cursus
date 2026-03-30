NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRC = src/main.c src/error_handling.c src/arg_parse.c src/init_structs.c src/resources.c \
      src/free_resources.c src/tasks.c src/death_checker.c src/time.c src/task_utils.c \
      src/philo_task.c src/forks.c src/general_utils.c src/general_utils2.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re