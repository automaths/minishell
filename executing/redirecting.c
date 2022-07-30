/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:34:47 by nimrod            #+#    #+#             */
/*   Updated: 2022/07/30 15:00:40 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool	init_fd_in_bis(t_command *cmd, t_token *the_one)
{
	if (the_one != NULL)
	{
		if (the_one->type == HEREDOC)
			cmd->fd_in = opening_heredoc(the_one->content);
		if (the_one->type == READ)
			cmd->fd_in = opening_standard_input(the_one->content);
	}
	if (the_one == NULL && cmd->is_piped == 0)
		cmd->fd_in = 0;
	return (1);
}

bool	init_fd_in(t_command *cmd)
{
	t_token	*tmp;
	t_token	*the_one;

	tmp = cmd->redir;
	the_one = NULL;
	while (tmp != NULL)
	{
		if (tmp->type == HEREDOC || tmp->type == READ)
		{
			if (tmp->type == READ)
			{
				if (check_fd_in(tmp->content) == 0)
					return (0);
			}
			the_one = tmp;
		}
		tmp = tmp->next;
	}
	init_fd_in_bis(cmd, the_one);
	return (1);
}

int	init_fd_out(t_command *cmd)
{
	t_token	*redir;

	redir = last_redir(cmd);
	if (redir != NULL)
	{
		if (redir->type == APPEND)
			cmd->fd_out = opening_append(redir->content);
		if (redir->type == WRITE)
			cmd->fd_out = opening_standard_output(redir->content);
	}
	if (cmd->next != NULL)
		piping(cmd, redir);
	if (redir == NULL && cmd->next == NULL)
		cmd->fd_out = 1;
	return (1);
}

void	piping(t_command *cmd, t_token *redir)
{
	if (pipe(cmd->fd) == -1)
		return ;
	if (redir == NULL)
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
