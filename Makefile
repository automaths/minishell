SRCS			=	./utils_one.c \
					./utils_two.c \
					./utils_parsing.c \
					./utils_structuring_one.c \
					./utils_structuring_two.c \
					./utils_structuring_three.c \
					./utils_redirectionning.c \
					./utils_opening_fds.c \
					./utils_fding.c \
					./utils_environning_one.c \
					./utils_environning_two.c \
					./utils_environning_three.c \
					./utils_builts.c \
					./structuring.c \
					./executing.c \
					./groshell.c \
					./parsing.c \
					./freeing_parsing.c \
					./environning.c \
					./builts_echo.c \
					./builts_env.c \
					./builts_pwd.c \
					./builts_export.c \
					

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