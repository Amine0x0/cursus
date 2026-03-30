NAME = phonebook
SRCS = srcs/main.cpp \
		srcs/impl/Contact.cpp \
		srcs/impl/PhoneBook.cpp \
		srcs/impl/ConsoleUI.cpp
OBJS = $(SRCS:.cpp=.o)
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

HEADERS = include/PhoneBook.hpp

all: $(NAME)

$(NAME): $(OBJS) 
	c++ $(CPPFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp $(HEADERS)
	c++ $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
