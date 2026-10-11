PROGRAM = c++
PROGRAMFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = identify

SRCS = main.cpp Base.cpp A.cpp B.cpp C.cpp funcs.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(PROGRAM) $(PROGRAMFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp Base.hpp A.hpp B.hpp C.hpp funcs.hpp
	$(PROGRAM) $(PROGRAMFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re