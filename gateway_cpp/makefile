NAME  = gateway.out

RM          = rm -f

CXX         = clang++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98

INCLUDE     =	-I .

LIBRARY =
COMPILE = $(CXX) $(CXXFLAGS) $(INCLUDE) $(DEBUG_OPTION)
LINK = $(CXX) $(CXXFLAGS) $(INCLUDE) $(DEBUG_OPTION) $(LIBRARY)

SRCS        =	Utility.cpp \
              Application.cpp \
              Select.cpp \
              LocalServer.cpp \
              Stream.cpp \
              Http.cpp \
              main.cpp

OBJS        = $(SRCS:.cpp=.o)



.PHONY: all compile debug setdebug clean fclean re
all:  $(NAME)

compile:  $(OBJS)

debug:  clean setdebug $(NAME)
setdebug:
				$(eval DEBUG_OPTION = -g)

clean:
				$(RM) $(OBJS)
fclean: clean
				$(RM) $(NAME)

re: fclean all




$(NAME):  $(OBJS) main.o
				$(LINK) -o $@ $^

test: $(OBJS) test.o
				$(LINK) -o $@ $^

%.o:  %.cpp
				$(COMPILE) -o $@ -c $<
