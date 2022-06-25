#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include "./libft/libft.h"
# include "errno.h"

typedef struct s_token {
	char *content;
	struct s_token *next;
} t_token;

typedef struct s_command {
	t_token *arg;
	t_token *redir;
	int fd_in;
	int fd_out;
	struct s_command *next;
} t_command;

void	parse_line(char *str, char **envp);

bool	is_arg(char *str);
bool	is_redirection(char *str);
bool	is_new_cmd(char *str);

#endif

