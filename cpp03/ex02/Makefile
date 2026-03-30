NAME = FragTrap
SRCS = main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp
COMPILER = c++
HEADER = ClapTrap.hpp ScavTrap.hpp FragTrap.hpp
FLAGS = -Wall -Wextra -Werror -std=c++98
OBJ = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILER) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(HEADER)
	$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
