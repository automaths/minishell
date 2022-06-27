/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirectionning_one.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:28:22 by nsartral          #+#    #+#             */
/*   Updated: 2022/06/27 12:33:17 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	piping(t_command *cmd)
{
	if (pipe(cmd->fd) == -1)
		return ;
	cmd->fd_out = cmd->fd[1];
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

void	init_fd_out(t_command *cmd)
{
	t_token		*tmp;
	char		*content;

	tmp = cmd->redir;
	content = NULL;
	while (tmp != NULL)
	{
		if (is_redirection(tmp->content) == 2)
			content = tmp->content;
		tmp = tmp->next;
	}
	if (content != NULL)
	{
		if (is_append(content) == 2)
			cmd->fd_out = opening_append(content);
		if (is_append(content) == 1)
			cmd->fd_out = opening_standard_output(content);
	}
	if (content == NULL && cmd->next != NULL)
		piping(cmd);
	if (content == NULL && cmd->next == NULL)
		cmd->fd_out = 1;
}

void	redirectionning(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		init_fd_in(tmp);
		init_fd_out(tmp);
		tmp = tmp->next;
	}
}
