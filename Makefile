SRCS			=	./groshell.c \
					./parsing/lexer/lexer.c \
					./parsing/lexer/lexer_utils.c \
					./parsing/parser/parser.c \
					./parsing/parser/parser_utils.c \
					./parsing/parser/parsing_spliting.c \
					./parsing/expander/expand.c \
					./parsing/expander/expand_utils.c \
					./utils/env_char_to_lst.c \
					./utils/env_lst_to_char.c \
					./utils/freeing.c \
					./utils/libft_plus.c \
					./utils/printing.c \
					./tmp_libft/libft.c \
					./executing/builtsing_fork.c \
					./executing/builtsing_nofork.c \
					./executing/executing.c \
					./executing/execving.c \
					./executing/opening_fds.c \
					./executing/parsing_arg.c \
					./executing/redirecting.c \
					./executing/parsing_arg_new.c \
					./executing/builts/cd.c \
					./executing/builts/echo.c \
					./executing/builts/env.c \
					./executing/builts/exit.c \
					./executing/builts/export.c \
					./executing/builts/pwd.c \
					./executing/builts/unset.c \
					

OBJS			= 	$(SRCS:.c=.o)

# LIBS			=  -L ./libft -lft

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