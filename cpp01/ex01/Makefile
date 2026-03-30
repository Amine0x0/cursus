CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = Horde
SRC = main.cpp Zombie.cpp ZombieHorde.cpp
OBJ = $(SRC:.cpp=.o)
HDR = Zombie.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(CPPFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp $(HDR)
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
