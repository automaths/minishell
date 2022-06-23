SRCS			=	./command_generator.c

OBJS			= 	$(SRCS:.c=.o)

LIBS			=  -L ./libft -lft

CC				= 	gcc
RM				= 	rm -f
CFLAGS			= 	-Wall -Wextra -Werror

NAME			= 	test

all:			$(NAME)

$(NAME):		$(OBJS)
				@make -C ./libft
				gcc $(CFLAGS) -g3 -o $(NAME) $(OBJS) $(LIBS)

clean:
				$(RM) $(OBJS)
				$(RM) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME) $(OBJS)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus