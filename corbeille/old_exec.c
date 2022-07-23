#include "../execution.h"

// t_env	*exec_command(t_command *cmd)
// {
// 	t_command	*tmp;

// 	if (!cmd)
// 		return (NULL);
// 	tmp = cmd;
// 	if (redirectionning(tmp) == 0)
// 		return (NULL);
// 	while (tmp != NULL)
// 	{
// 		if (parse_argument(tmp) == 0)
// 		{
// 			if (tmp->next != NULL)
// 				tmp->next->fd_in = -1;
// 		}
// 		else
// 		{
// 			if (check_builts(tmp->arg->argz))
// 			{
// 				if (check_builts_nofork(tmp->arg->argz))
// 					exec_token_builts_nofork(tmp);
// 				else
// 					exec_token_builts(tmp);
// 			}
// 			else
// 				exec_token(tmp);
// 		}
// 		print_fd(tmp->fd_in);
// 		print_fd(tmp->fd_out);
// 		tmp = tmp->next;
// 		if (tmp == NULL)
// 			break ;
// 	}
// 	waitpiding(cmd);
// 	closing_fd(cmd);
// 	tmp = cmd;
// 	while (tmp->next != NULL)
// 		tmp = tmp->next;
// 	return (tmp->env);
// }

// bool	check_fd_out(char *content, t_token *redir)
// {
// 	int		fd;
// 	char	*file;

// 	file = ft_strtrim(content, "> ");
// 	if (access(file, F_OK) == 0)
// 	{
// 		if (access(file, W_OK) == -1)
// 			return (writing_error(ft_strtrim(file, "> "), WRONG_CHMOD), 0);
// 	}
// 	if (redir != NULL)
// 	{
// 		if (is_append(content) == 2)
// 			fd = open(file, O_CREAT | O_RDWR, 0644);
// 		if (is_append(content) == 1)
// 			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 		if (fd == -1)
// 			return (writing("cant open file", " "), -1);
// 		close(fd);
// 	}
// 	return (1);
// }

// char	*last_redir(t_command *cmd)
// {
// 	t_token	*tmp;
// 	char	*content;

// 	tmp = cmd->redir;
// 	content = NULL;
// 	while (tmp != NULL)
// 	{
// 		if (is_redirection(tmp->content) == 2)
// 		{
// 			if (check_fd_out(tmp->content, tmp->next) == 0)
// 				return (0);
// 			content = tmp->content;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (content);
// }