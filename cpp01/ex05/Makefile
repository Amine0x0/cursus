CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = Harl
SRC = main.cpp Harl.cpp
OBJ = $(SRC:.cpp=.o)
HDR = Harl.hpp

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
