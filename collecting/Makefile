SRCS			=	./garbage_collector.c \

OBJS			= 	$(SRCS:.c=.o)

CC				= 	gcc

RM				= 	rm -f

CFLAGS			= 	-Wall -Wextra -Werror

NAME			= 	a.out

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:		all clean fclean re