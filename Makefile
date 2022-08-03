SRCS			=	./groshell.c \
					./parsing/lexer/lexer_one.c \
					./parsing/lexer/lexer_two.c \
					./parsing/lexer/lexer_utils.c \
					./parsing/lexer/check_quotes.c \
					./parsing/parser/parser.c \
					./parsing/parser/post_expand.c \
					./parsing/parser/parser_utils_one.c \
					./parsing/parser/parser_utils_two.c \
					./parsing/expander/expand.c \
					./parsing/expander/expand_redir_list.c \
					./parsing/expander/expand_utils.c \
					./parsing/expander/expand_utils_two.c \
					./parsing/expander/delete_quote.c \
					./parsing/expander/delete_quote_redir_list.c \
					./parsing/expander/return_value.c \
					./executing/builtsing_fork.c \
					./executing/builtsing_nofork.c \
					./executing/executing.c \
					./executing/execving.c \
					./executing/local_exec.c \
					./executing/opening_fds.c \
					./executing/parsing_arg.c \
					./executing/redirecting_heredoc.c \
					./executing/redirecting.c \
					./executing/redirecting_utils.c \
					./executing/parsing_arg_new.c \
					./executing/builts/cd.c \
					./executing/builts/echo.c \
					./executing/builts/env.c \
					./executing/builts/exit.c \
					./executing/builts/export.c \
					./executing/builts/export_utils_one.c \
					./executing/builts/export_utils_two.c \
					./executing/builts/pwd.c \
					./executing/builts/unset.c \
					./utils/env_char_to_lst.c \
					./utils/env_char_to_lst_utils.c \
					./utils/env_lst_to_char.c \
					./utils/exiting.c \
					./utils/erroring.c \
					./utils/printing.c \
					./utils/singleton.c \
					./utils/garbage_collector.c \
					./utils/tmp_debug.c \
					./utils/ft_split.c \
					./utils/ft_strtrim.c \
					./utils/libft_one.c \
					./utils/libft_two.c \
					./utils/utils_one.c \
					./utils/signal.c \
					./utils/ft_itoa.c \
					

OBJS			= 	$(SRCS:.c=.o)

CC				= 	gcc

RM				= 	rm -f

CFLAGS			= 	-Wall -Wextra -Werror

NAME			= 	minishell

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:		all clean fclean re