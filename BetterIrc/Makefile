NAME = ircserv

PROGRAM = c++
PROGRAMFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = src/main.cpp \
       src/Server.cpp \
       src/ServerIO.cpp \
       src/ServerRegistration.cpp \
       src/ServerMessaging.cpp \
       src/ServerChannels.cpp \
       src/ServerModes.cpp \
       src/Session.cpp \
       src/Channel.cpp \
       src/PacketDecoder.cpp \
       src/Replies.cpp \
       src/Arguments.cpp \
       src/Signals.cpp \
       src/tooling.cpp

HEADERS = includes/Server.hpp \
          includes/Session.hpp \
          includes/Channel.hpp \
          includes/PacketDecoder.hpp \
          includes/Replies.hpp \
          includes/Arguments.hpp \
          includes/Signals.hpp \
          includes/MasterControlFlags.hpp \
          includes/Tooling.hpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(PROGRAM) $(PROGRAMFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(PROGRAM) $(PROGRAMFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
