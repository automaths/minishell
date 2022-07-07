#include "../execution.h"

bool	check_fd_in(char *content)
{
	content = ft_strtrim(content, "< ");
	if (access(content, F_OK) != 0)
		return (writing_error(ft_strtrim(content, "> "), NO_FILE), 0);
	if (access(content, R_OK) == -1)
		return (writing_error(ft_strtrim(content, "> "), WRONG_CHMOD), 0);
	return (1);
}

bool	check_fd_out(char *content, t_token *redir)
{
	int		fd;
	char	*file;

	file = ft_strtrim(content, "> ");
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return (writing_error(ft_strtrim(file, "> "), WRONG_CHMOD), 0);
	}
	if (redir != NULL)
	{
		if (is_append(content) == 2)
			fd = open(file, O_CREAT | O_RDWR, 0644);
		if (is_append(content) == 1)
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			return (writing("cant open file", " "), -1);
		close(fd);
	}
	return (1);
}

char	*last_redir(t_command *cmd)
{
	t_token	*tmp;
	char	*content;

	tmp = cmd->redir;
	content = NULL;
	while (tmp != NULL)
	{
		if (is_redirection(tmp->content) == 2)
		{
			if (check_fd_out(tmp->content, tmp->next) == 0)
				return (0);
			content = tmp->content;
		}
		tmp = tmp->next;
	}
	return (content);
}

int	is_heredoc(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '<')
			++j;
	}
	if (j == 2)
		return (2);
	if (j == 1)
		return (1);
	return (0);
}

int	is_append(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '>')
			++j;
	}
	if (j == 2)
		return (2);
	if (j == 1)
		return (1);
	return (0);
}
