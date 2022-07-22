SRCS			=	./builts/cd.c \
					./builts/echo.c \
					./builts/env.c \
					./builts/exit.c \
					./builts/export.c \
					./builts/pwd.c \
					./builts/unset.c \
					./executing/builtsing_fork.c \
					./executing/builtsing_nofork.c \
					./executing/checking_fds.c \
					./executing/executing.c \
					./executing/execving.c \
					./executing/opening_fds.c \
					./executing/parsing_arg.c \
					./executing/redirecting.c \
					./parsing/creating_tkn_cmd.c \
					./parsing/environning.c \
					./parsing/groshell.c \
					./parsing/parsing_spliting.c \
					./utils/env_char_to_lst.c \
					./utils/env_lst_to_char.c \
					./utils/freeing.c \
					./utils/libft_plus.c \
					./utils/printing.c \
					./tmp_libft/libft.c \
					./parsing_lexer/step_one.c \
					./parsing_lexer/step_one_utils.c \
					./parsing_cmd/step_two.c \
					./parsing_cmd/command_validation.c \
					./execution_new/executing_new.c \
					./execution_new/redirecting_new.c \
					

OBJS			= 	$(SRCS:.c=.o)

# LIBS			=  -L ./libft -lft

CC				= 	gcc
RM				= 	rm -f
CFLAGS			= 	-Wall -Wextra -Werror

all:			$(OBJS)
				gcc $(CFLAGS) -g3 $(OBJS)

clean:
				$(RM) $(OBJS)
				$(RM) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME) $(OBJS)

re:				all

.PHONY:			all clean fclean re bonus