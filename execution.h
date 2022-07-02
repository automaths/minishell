/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:10:49 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/02 20:31:14 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#define CMD_NOT_FOUND 1
#define NO_FILE 2
#define WRONG_CHMOD 3

typedef struct s_token {
	char			*content;
	char			**envp;
	char			**unix_paths;
	char			**argz;
	char			*command;
	char			*path;
	int				pid;
	struct s_token	*next;
}	t_token;

typedef struct s_command {
	t_token				*arg;
	t_token				*redir;
	int					is_piped;
	int					fd[2];
	int					fd_in;
	int					fd_out;
	struct s_command	*next;
}	t_command;

// <<a : 
// 		heredoc link avec le fichier temporaire
// <a : 
// 		si mauvais chmod ou existe pas erreur traite aucune commande 
// 		si a la suite le dernier est ouvert
// >a : 
// 		cree un fichier chmod 644 si existe pas 
// 		si mauvais chmod erreur traite aucune commande
// 		si elle se suive seulement derniere
// >>a : 
// 		comme >a mais en mode append
t_command		*parse_line(char *str);
//EXECUTING
void			last_exec(t_command *cmd, char **envp);
bool			exec_command(t_command *cmd, char **envp);
//FREEING_PARSING
void			freeing_unix(t_token *arg);
void			freeing_command(t_token *arg);
void			freeing_path(t_token *arg);
void			freeing_argz(t_token *arg);
void			freeing_path_and_argz(t_token *arg);
//PARSING
bool			command_trim(t_token *arg);
bool			find_path(t_token *arg, char *unix_path);
bool			get_the_path(t_token *arg);
bool			parse_argument(t_token *arg, char **envp);
//STRUCTURING
t_command		*parse_line(char *str);
//UTILS_PARSING
void			print_parsed(t_command *cmd);
void			token_initing(t_token *arg, char **envp);
char			*ft_strjoin_new(char *s1, char *s2, int flag);
bool			is_whitespace(char c);
bool			is_lowercase(char c);
bool			is_printable_except_space(char c);
//UTILS_STRUCTURING_ONE
t_command		*new_cmd(int i);
t_token			*new_tkn(char *arg);
void			add_back_tkn(t_token **tkn, t_token *new);
void			add_back_cmd(t_command **cmd, t_command *new);
//UTILS_STRUCTURING_TWO
int				count_commands(char *str);
void			print_all(t_command *cmd);
bool			is_arg(char *str);
int				is_redirection(char *str);
bool			is_new_cmd(char *str);
//UTILS_STRUCTURING_THREE
char			*quoting_ruling(char *str);
char			**split_cleaning(char **split);
//UTILS
void			writing(char *intro, char *content);
void			print_fd(int fd);
int				is_heredoc(char *str);
int				is_append(char *str);
void			writing_error(char *str, int num);
//UTILS_REDIRECTIONNING_ONE
void			piping(t_command *cmd);
void			init_fd_in(t_command *cmd);
int				init_fd_out(t_command *cmd);
int				redirectionning(t_command *cmd);
bool			check_fd_out(char *content, t_token *redir);
//UTILS_REDIRECTIONNING_TWO
int				opening_append(char *content);
int				opening_standard_output(char *content);
int				opening_heredoc(char *content);
int				opening_standard_input(char *content);
//UTILS_INPUTING
#endif
