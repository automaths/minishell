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
	char **envp;
	char **unix_paths;
	char **argz;
	char *command;
	char *path;
	
	struct s_token *next;
} t_token;

typedef struct s_command {
	t_token *arg;
	t_token *redir;
	int fd_in;
	int fd_out;
	struct s_command *next;
} t_command;

t_command	*parse_line(char *str, char **envp);

bool	is_arg(char *str);
bool	is_redirection(char *str);
bool	is_new_cmd(char *str);

void	writing(char *intro, char *content);
void	print_all(t_command *cmd);

void	exec_command(t_command *cmd, char **envp);
bool	parse_argument(t_token *arg, char **envp);
void	print_parsed(t_command *cmd);

void	freeing_unix(t_token *arg);
void	freeing_command(t_token *arg);
void	freeing_path(t_token *arg);
void	freeing_argz(t_token *arg);
void	freeing_path_and_argz(t_token *arg);

bool	is_lowercase(char c);
bool	is_whitespace(char c);

#endif

