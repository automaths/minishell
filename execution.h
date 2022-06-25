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

//EXECUTING
void	last_exec(t_command *cmd, char **envp);
void	exec_command(t_command *cmd, char **envp);
//FREEING_PARSING
void	freeing_unix(t_token *arg);
void	freeing_command(t_token *arg);
void	freeing_path(t_token *arg);
void	freeing_argz(t_token *arg);
void	freeing_path_and_argz(t_token *arg);
//PARSING
bool	command_trim(t_token *arg);
bool	find_path(t_token *arg, char *unix_path);
bool	get_the_path(t_token *arg);
bool	parse_argument(t_token *arg, char **envp);
//STRUCTURING
t_command	*parse_line(char *str, char **envp);
//UTILS_PARSING
void	print_parsed(t_command *cmd);
void	token_initing(t_token *arg, char **envp);
char	*ft_strjoin_new(char *s1, char *s2, int flag);
bool	is_whitespace(char c);
bool	is_lowercase(char c);
//UTILS_STRUCTURING_ONE
t_command	*new_cmd(int fd_in, int fd_out);
t_token	*new_tkn(char *arg);
void	add_back_tkn(t_token **tkn, t_token *new);
void	add_back_cmd(t_command **cmd, t_command *new);
//UTILS_STRUCTURING_TWO
int	count_commands(char *str);
void	print_all(t_command *cmd);
bool	is_arg(char *str);
bool	is_redirection(char *str);
bool	is_new_cmd(char *str);
//UTILS
void	writing(char *intro, char *content);

#endif

