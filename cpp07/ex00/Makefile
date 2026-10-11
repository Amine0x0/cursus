NAME = exec

PROGRAM = c++
PROGRAMFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(PROGRAM) $(PROGRAMFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp ./whatever.hpp
	$(PROGRAM) $(PROGRAMFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
