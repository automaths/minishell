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

typedef struct s_command {
	char *arg;
	int nb_argz;
	int **redirection;
	int nb_redirection;
	int fd_in;
	int fd_out;
	struct s_list *next;
} t_command;

#endif

