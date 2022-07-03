/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:34:47 by nimrod            #+#    #+#             */
/*   Updated: 2022/07/03 13:48:56 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	check_fd_in(char *content)
{
	content = ft_strtrim(content, "< ");
	if (access(content, F_OK) != 0)
		return (writing_error(ft_strtrim(content, "> "), NO_FILE), 0);
	if (access(content, R_OK) == -1)
		return (writing_error(ft_strtrim(content, "> "), WRONG_CHMOD), 0);
	return (1);
}

bool	init_fd_in(t_command *cmd)
{
	t_token		*tmp;
	char		*content;

	tmp = cmd->redir;
	content = NULL;
	while (tmp != NULL)
	{
		if (is_redirection(tmp->content) == 1)
		{
			if (check_fd_in(tmp->content) == 0)
				return (0);
			content = tmp->content;
		}
		tmp = tmp->next;
	}
	if (content != NULL)
	{
		if (is_heredoc(content) == 2)
			cmd->fd_in = opening_heredoc(content);
		if (is_heredoc(content) == 1)
			cmd->fd_in = opening_standard_input(content);
	}
	if (content == NULL && cmd->is_piped == 0)
		cmd->fd_in = 0;
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

int	init_fd_out(t_command *cmd)
{
	char		*content;

	content = last_redir(cmd);
	if (content != NULL)
	{
		if (is_append(content) == 2)
			cmd->fd_out = opening_append(content);
		if (is_append(content) == 1)
			cmd->fd_out = opening_standard_output(content);
	}
	if (cmd->next != NULL)
		piping(cmd, content);
	if (content == NULL && cmd->next == NULL)
		cmd->fd_out = 1;
	return (1);
}
