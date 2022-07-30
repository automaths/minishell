SRCS			=	./current_exec.c \
					
OBJS			= 	$(SRCS:.c=.o)

CC				= 	gcc
RM				= 	rm -f
CFLAGS			= 	-Wall -Wextra -Werror

all:			$(OBJS)
				gcc $(CFLAGS) -g3 $(OBJS) -lreadline

clean:
				$(RM) $(OBJS)
				$(RM) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME) $(OBJS)

re:				all

.PHONY:			all clean fclean re bonus