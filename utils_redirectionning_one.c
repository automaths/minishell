/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirectionning_one.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:28:22 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/02 23:13:18 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	piping(t_command *cmd, char *content)
{
	if (pipe(cmd->fd) == -1)
		return ;
	if (content == NULL)
		cmd->fd_out = cmd->fd[1];
	else 
		close (cmd->fd[1]);
	cmd->next->fd_in = cmd->fd[0];
	cmd->next->is_piped = 1;
}

void	init_fd_in(t_command *cmd)
{
	t_token		*tmp;
	char		*content;

	tmp = cmd->redir;
	content = NULL;
	while (tmp != NULL)
	{
		if (is_redirection(tmp->content) == 1)
			content = tmp->content;
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
}

bool	check_fd_out(char *content, t_token *redir)
{
	int fd; 

	content = ft_strtrim(content, "> ");
	if (access(content, F_OK) == 0)
	{
		if (access(content, W_OK) == -1)
			return (writing_error(ft_strtrim(content, "> "), WRONG_CHMOD), 0);
	}
	if (redir != NULL)
	{
		fd = open(content, O_CREAT | O_RDWR, 0644);
		if (fd == -1)
			return (writing("cant open file", " "), -1);
		close(fd);	
	}
	return (1);
}

int	init_fd_out(t_command *cmd)
{
	t_token		*tmp;
	char		*content;

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

int	redirectionning(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		init_fd_in(tmp);
		if (init_fd_out(tmp) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
