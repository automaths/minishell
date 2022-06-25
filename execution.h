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
	char *arg;
	struct s_token *next;
} t_token;

typedef struct s_command {
	t_token *argz;
	t_token *redir;
	int fd_in;
	int fd_out;
	struct s_command *next;
} t_command;

void	env(int fd, char **envp);
void	pwd(int fd);
void	echo(int fd, int mode, char *str);
bool	cd(char *arg);
void	exiting(void);

// void	ft_lstadd_back(t_list **lst, t_list *new);
// t_list	*ft_lstmap(t_list *lst);
t_command	*new_command(int fd_in, int fd_out);
// int	ft_lstsize(t_list *lst);
// int	ft_lstcontent(t_list *lst, int index);

void	parse_line(char *str, char **envp);

#endif

