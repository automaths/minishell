/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:34:47 by nimrod            #+#    #+#             */
/*   Updated: 2022/07/07 18:17:31 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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

int	redirectionning(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		if (init_fd_in(tmp) == 0)
			return (0);
		if (init_fd_out(tmp) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
