/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:10:49 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/02 14:09:41 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GROSHELL_H
# define GROSHELL_H
// ========================================================================= //
//                                   Library                                 //
// ========================================================================= //

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

// ========================================================================= //
//                                    Enum                                   //
// ========================================================================= //

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

typedef enum e_garbage
{
	S_CHAR = 1,
	D_CHAR,
	FST,
	CMD,
	TKN,
	ENV,
}	t_enum_garbage;

// ========================================================================= //
//                                Structure                                  //
// ========================================================================= //

typedef struct s_first
{
	int				type;
	char			*content;
	struct s_first	*next;
}	t_first;

typedef struct s_garbage	t_garbage;

typedef struct s_env
{
	char			*name;
	char			*content;
	t_garbage		**garbage;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*content;
	int				type;
	char			**unix_paths;
	char			**argz;
	char			*command;
	char			*path;
	int				pid;
	t_garbage		**garbage;
	struct s_token	*next;
}	t_token;

typedef struct s_command	t_command;

typedef struct s_garbage
{
	char				**d_char;
	char				*s_char;
	t_first				*fst;
	t_command			*cmd;
	t_token				*tkn;
	t_env				*env;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_command
{
	t_token				*arg;
	t_token				*redir;
	t_env				*env;
	t_garbage			**garbage;
	char				**envp_char;
	int					is_piped;
	int					is_piping;
	int					is_exec;
	int					fd[2];
	int					fd_in;
	int					fd_out;
	int					previous_fd;
	struct s_command	*next;
}	t_command;

// ========================================================================= //
//                                Executing                                  //
// ========================================================================= //

// executing/builts/
void		exec_cd(t_command *cmd);
char		*find_content_cd(char *name, t_env *env);
void		exec_echo(t_command *cmd);
void		exec_env(t_command *cmd);
int			update_env(char *name, char *content, t_env *env);
void		exec_exit(t_command *cmd);
void		exec_export(t_command *cmd);
void		print_export(t_command *cmd);
void		export_shlvl(t_command *cmd, bool add);
void		exec_pwd(t_command *cmd);
void		exec_unset(t_command *cmd);

// executing/builts/export_utils
char		*export_content(char *str, t_garbage **garbage);
char		*export_name(char *str, t_garbage **garbage);
int			check_export(char *str);
bool		check_equal(char *str);
bool		is_export(char c);
void		add_back_env(char *name, char *content, t_env *env);
void		update_all_envz(t_command *cmd, t_env *env);
void		add_back_lst(t_env **lst, t_env *new);

// executing/builtsing_fork.c
bool		check_builts(char **argz);
void		exec_builts(t_command *cmd);
void		forking_builts(t_command *cmd);
void		exec_token_builts(t_command *cmd);

// executing/builtsing_nofork.c
bool		check_builts_nofork(char **argz);
void		exec_token_builts_nofork(t_command *cmd);

// executing/executing.c
void		closing_fd(t_command *cmd);
void		waitpiding(t_command *cmd);
t_env		*exec_command(t_command *cmd);

// executing/execving.c
void		forking(t_command *cmd);
void		exec_token(t_command *cmd);

// executing/local_exec.c
bool		check_local_exec(char *command);
void		local_forking(t_command *cmd);
void		local_exec(t_command *cmd);

// executing/opening_fds.c
int			opening_append(char *content, t_garbage **garbage);
int			opening_standard_output(char *content, t_garbage **garbage);
int			opening_heredoc(char *content, t_garbage **garbage);
int			opening_standard_input(char *content, t_garbage **garbage);

// executing/parsing_arg_new.c
bool		get_the_path(t_command *cmd);
bool		parse_argument(t_command *cmd);

// executing/parsing_arg.c
void		token_initing(t_command *cmd);
bool		command_trim(t_command *cmd);
bool		find_path(t_token *arg, char *unix_path);
bool		is_builts(char *command);
bool		check_absolute(t_command *cmd);

// executing/redirecting.c
bool		check_fd_in(char *content, t_garbage **garbage);
bool		init_fd_in(t_command *cmd);
bool		check_fd_out(t_token *redir, t_garbage **garbage);
t_token		*last_redir(t_command *cmd);
int			init_fd_out(t_command *cmd);
void		piping(t_command *cmd, t_token *redir);
int			redirectionning(t_command *cmd);

// ========================================================================= //
//                                 Parsing                                   //
// ========================================================================= //

// parsing/expand/expand.c
int			replace_all_variable(t_command *cmd, t_env *env);
int			replace_variable(t_command *cmd, t_env *env);
char		*replace_one_variable(char *str, t_env *env, int i, t_command *cmd);
char		*string_with_var_value(char *cmd, char *name, \
				int size_old_var, t_command *t_cmd);
char		*find_variable_value(char *name, t_env *env);

// parsing/expand/expand_redir_list.c
int			delete_redir_char_in_redir_list(t_command *cmd);
int			replace_variable_redir(t_command *cmd, t_env *env);

// parsing/expand/return_value.c
char		*string_with_return_var_value(char *cmd, char *name, \
				int size_old_var, t_command *t_cmd);
char		*replace_one_return_value(char *str, t_command *cmd);
int			replace_return_value(t_command *cmd);

// parsing/expand/expand_utils.c
void		parse_dollars(t_command *cmd);
void		parse_dollars_redir(t_command *cmd);
void		replace_negativ_char(t_command *cmd);
void		replace_negativ_char_redir(t_command *cmd);
int			what_state(char *str, int j);
int			ft_isalnum(int c);

// parsing/expand/delete_quote.c
void		negativ_quote(char *str);
char		*del_one_neg_quotes(char *str, t_command *cmd);
int			del_all_neg_quotes(t_command *cmd);
int			del_quotes(t_command *cmd);

// parsing/expand/delete_quote_redir_list.c
int			del_all_neg_quotes_redir(t_command *cmd);
int			delete_quotes_redir_list(t_command *cmd);

// parsing/parser/parser.c
bool		redirection_validation(t_first *uno);
bool		pipes_validation(t_first *uno);
bool		command_validation(t_first *uno);

// parsing/parser/parser_utils.c
t_command	*new_cmd(t_env *env, t_garbage **garbage);
void		add_back_cmd(t_command **cmd, t_command *new);
t_token		*new_tkn(char *arg, int type, t_garbage **garbage);
void		add_back_tkn(t_token **tkn, t_token *new);
t_command	*step_two(t_first *uno, t_env *env, t_garbage **garbage);

// parsing/lexer/lexer_one.c
int			lexer_id_one(char c, int *mode);
int			lexer_id_two(t_first **uno, char *str, int *mode, \
				t_garbage **garbage);
int			lexer_id_three(t_first **uno, char *str, int *mode, \
				t_garbage **garbage);
int			lexer_id_four(t_first **uno, char *str, int *mode, \
				t_garbage **garbage);
t_first		*lexer(char *str, t_garbage **garbage);

// parsing/lexer/lexer_utils.c
void		print_lexer(t_first *uno);
void		add_back_uno(t_first **uno, t_first *new);
char		*alloc_content(char *str, unsigned int size, t_garbage **garbage);
int			actual_mode(char c);

//parsing/lexer/check_quotes.c
bool		check_quotes(char *str);

// parsing/lexer/lexer_utils_two.c
t_first		*new_uno(int type, char *content, t_garbage **garbage);
void		add_back_uno(t_first **uno, t_first *new);
void		print_lexer(t_first *uno);

// ========================================================================= //
//                                  Utils                                    //
// ========================================================================= //

// utils/env_char_to_lst.c
t_env		*new_lst(char *name, char *content, t_garbage **garbage);
t_env		*new_env_lst(char *name, char *content);
void		add_back_env_lst(t_env **lst, t_env *new);
char		*get_content(char *envp, t_garbage **garbage);
char		*get_name(char *envp, t_garbage **garbage);
int			has_equal(char *str);
bool		check_envp(char **envp);
t_env		*env_to_list(char **envp, t_garbage **garbage);

// utils/env_lst_to_char.c
int			lst_len(t_env *env);
char		*alloc_line(char *name, char *content, t_garbage **garbage);
char		**envp_to_char(t_env *env);

//utils/erroring.c 
void		ft_error(char *str, char *next, int error_type, bool update);

// utils/ft_split.c
char		**ft_split(char *s, char c, t_garbage **garbage);

//utils/singleton.c
int			singleton(int set, bool write);

//utils/garbage_collector.c
void		updator_next(t_command *cmd);
void		updator_all(t_command *cmd);
void		init_garbage(t_garbage **garbage);
t_garbage	*new_garbage(void *content, int type);
void		add_garbage(t_garbage **grb, t_garbage *new);
void		clean_garbage(t_garbage **grb);

// utils/utils_one.c
int			ft_atoi(const char *str);
char		*ft_strdup(const char *str, t_garbage **garbage);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

// utils/utils_two.c
char		*ft_strtrim(const char *s1, const char *set, t_garbage **garbage);
char		*ft_strjoin(char const *s1, char const *s2, t_garbage **garbage);

// utils/utils_three.c
bool		is_whitespace(char c);
bool		is_lowercase(char c);
bool		is_printable_except_space(char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin_new(char *s1, char *s2, t_garbage **garbage);
void		ft_putnbr_fd(int n, int fd);

// utils/utils_four.c
int			strnstr_int(char *str, char *to_find);
void		writing_error(char *str, int num);
void		writing(char *intro, char *content);

// utils/ft_itoa.c
char		*ft_itoa(int nb, t_garbage **garbage);

// signaux
void		set_signal();
void		prompt_signal(int sig);
void		exit_fork();

// utils/exiting.c
void		exiting_malloc(t_garbage **garbage);

void		closing_next_fds(t_command *cmd);
void		print_fd(int fd);

#endif
