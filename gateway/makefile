NAME  = gateway.out
SRCS	= \
			  application.c \
			  buffer.c \
			  file.c \
			  protocol_dht.c \
			  select_context.c \
			  server.c \
			  utility.c \
			  gateway.c
OBJS	= $(SRCS:.c=.o)

CC			= clang
CFLAGS		= -Wall -Wextra -Werror

ABSTRACT_INCLUDE = .
INCLUDE		= $(addprefix -I ,$(ABSTRACT_INCLUDE))

LIBRARY		=
COMPILE		= $(CC) $(CFLAGS) $(INCLUDE) $(DEBUG_OPTION)
LINK		= $(CC) $(CFLAGS) $(INCLUDE) $(DEBUG_OPTION) $(LIBRARY)

RM			= rm -f



.PHONY:		all debug setdebug clean fclean re
all:		$(NAME)

debug:		clean setdebug $(CLIENT) $(SERVER)
setdebug:
			$(eval DEBUG_OPTION = -g)

clean:
			$(RM) $(OBJS)
fclean:		clean
			$(RM) $(CLIENT) $(SERVER)
re:			fclean all



$(NAME):	$(OBJS)
			$(LINK) -o $@ $^

%.o:		%.c
			$(COMPILE) -o $@ -c $<
