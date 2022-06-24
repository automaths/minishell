SRCS			=	./commands.c ./utils.c ./main.c ./builts/env.c ./builts/pwd.c ./builts/cd.c ./builts/echo.c

OBJS			= 	$(SRCS:.c=.o)

LIBS			=  -L ./libft -lft

CC				= 	gcc
RM				= 	rm -f
CFLAGS			= 	-Wall -Wextra -Werror

all:			$(OBJS)
				gcc $(CFLAGS) -g3 $(OBJS) $(LIBS)

clean:
				$(RM) $(OBJS)
				$(RM) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME) $(OBJS)

re:				all

.PHONY:			all clean fclean re bonus