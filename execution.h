/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:10:49 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/29 14:22:56 by nsartral         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "errno.h"
# include "./libft/libft.h"

typedef enum e_exec
{
	CMD_NOT_FOUND = 1,
	NO_FILE,
	WRONG_CHMOD,
}	t_enum_exec;

typedef enum e_type
{
	APPEND = 1,
	WRITE,
	HEREDOC,
	READ,
	PIPE,
	WORD,
	BEGIN,
}	t_enum_type;

typedef enum e_mode
{
	NEUTRAL_MODE = 1,
	R_REDIR_MODE,
	L_REDIR_MODE,
	WORD_MODE,
	DQUOTE_MODE,
	SQUOTE_MODE,
}	t_enum_mode;

typedef struct s_first {
	int type;
	char *content;
	struct s_first *next;
} t_first;

typedef struct s_env {
	char *name;
	char *content;
	struct s_env *next;
} t_env;

typedef struct s_token {
	char			*content;
	int				type;
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
	t_env				*env;
	char				**envp_char;
	int					is_piped;
	int					fd[2];
	int					fd_in;
	int					fd_out;
	struct s_command	*next;
}	t_command;





















//EXPANDER
char	*find_variable_value(char *name, t_env *env);
char	*string_with_var_value(char *cmd, char *name, int size_old_var);
char	*replace_one_variable(char *str, t_env *env, int i);
int	replace_variable(t_command *cmd, t_env *env);
int	replace_all_variable(t_command *cmd, t_env *env);
void	replace_negativ_char(t_command *cmd);
int	ft_isalnum(int c);
int	what_state(char *str, int j);
void	parse_dollars(t_command *cmd);

//BUILTS
//cd
void			exec_cd(t_command *cmd);
//echo
void			exec_echo(t_command *cmd);
//env
void			exec_env(t_command *cmd);
//exit
void			exec_exit(t_command *cmd);
//Eexport
void			exec_export(t_command *cmd);
//pwd
void			exec_pwd(t_command *cmd);
//unset
void			exec_unset(t_command *cmd);
//EXECUTING
//builtsing_fork
bool			check_builts(char **argz);
void			exec_builts(t_command *cmd);
void			forking_builts(t_command *cmd);
void			exec_token_builts(t_command *cmd);
//builtsing_nofork
bool			check_builts_nofork(char **argz);
void			exec_token_builts_nofork(t_command *cmd);
//checking_fds
bool			check_fd_in(char *content);
bool			check_fd_out(t_token *redir);
t_token			*last_redir(t_command *cmd);
//executing
void			closing_fd(t_command *cmd);
void			waitpiding(t_command *cmd);
t_env			*exec_command(t_command *cmd);
//execving
void			forking(t_command *cmd);
void			exec_token(t_command *cmd);
//opening_fds
int				opening_append(char *content);
int				opening_standard_output(char *content);
int				opening_heredoc(char *content);
int				opening_standard_input(char *content);
//parsing_arg
void			token_initing(t_command *cmd);
bool			command_trim(t_command *cmd);
bool			find_path(t_token *arg, char *unix_path);
bool			is_builts(char *command);
bool			get_the_path(t_command *cmd);
bool			parse_argument(t_command *cmd);
//redirecting
bool			init_fd_in(t_command *cmd);
int				init_fd_out(t_command *cmd);
void			piping(t_command *cmd, t_token *redir);
int				redirectionning(t_command *cmd);
//PARSING
//creating_tkn_cmd
t_command		*new_cmd(t_env *env);
void			add_back_cmd(t_command **cmd, t_command *new);
t_token			*new_tkn(char *arg, int type);
void			add_back_tkn(t_token **tkn, t_token *new);
//environning
bool			check_envz(char *str);
char			*updated_env(char *str, char *name, char *content);
char			*find_content(char *name, t_env *env);
char			*change_envz(char *str, t_env *env);
char			*environning(char *str, t_env *env);
//groshell
int				main(int argc, char **argv, char **envp);
//identifying
bool			is_arg(char *str);
int				is_redirection(t_token *redir);
bool			is_new_cmd(char *str);
//parsing_spliting
char			**spliting_plus(char *str);
char			*quoting_ruling(char *str);
char			**split_cleaning(char **split);
// t_command		*parse_line(char *str, t_env *env);
//UTILS
//env_char_to_lst
t_env			*new_lst(char *name, char *content);
void			add_back_lst(t_env **lst, t_env *new);
char			*get_content(char *envp);
char			*get_name(char *envp);
int				has_equal(char *str);
bool			check_envp(char **envp);
t_env			*env_to_list(char **envp);
//env_lst_to_char
int				lst_len(t_env *env);
char			*alloc_line(char *name, char *content);
char			**envp_to_char(t_env *env);
//freeing
void			freeing_unix(t_token *arg);
void			freeing_command(t_token *arg);
void			freeing_path(t_token *arg);
void			freeing_argz(t_token *arg);
void			freeing_path_and_argz(t_token *arg);
//libft_plus
int				strnstr_int(char *str, char *to_find);
bool			is_whitespace(char c);
bool			is_whitespace2(char c);
bool			is_lowercase(char c);
bool			is_printable_except_space(char c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strjoin_new(char *s1, char *s2, int flag);
//printing
void			print_all(t_command *cmd);
void			read_list(t_env *env);
void			writing_error(char *str, int num);
void			writing(char *intro, char *content);
void			print_fd(int fd);
void			print_parsed(t_command *cmd);
//step_one
t_first *step_one(char *str);
//set_one_utils
void print_step_one(t_first *uno);
void	add_back_uno(t_first **uno, t_first *new);
t_first	*new_uno(int type, char *content);
char *alloc_content(char *str, unsigned int size);
int actual_mode(char c);
//TMP_LIBFT
char	*ft_strtrim(const char *s1, const char *set);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	**ft_split(char const *s, char c);
int	ft_atoi(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
//STEP_TWO
t_command	*step_two(t_first *uno, t_env *env);
bool command_validation(t_first *uno);
bool	parse_argument(t_command *cmd);

#endif
