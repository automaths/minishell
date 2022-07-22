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
    t_token *tmp;
    t_token *the_one;

    tmp = cmd->redir;
    the_one = NULL;
    while (tmp != NULL)
    {
        if (tmp->type == HEREDOC || tmp->type == READ)
        {
            if (check_fd_in(tmp->content) == 0)
                return (0);
            the_one = tmp;
        }
        tmp = tmp->next;
    }
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

bool	check_fd_out(t_token *redir)
{
	int		fd;
	char	*file;

	file = ft_strtrim(redir->content, "> ");
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return (writing_error(ft_strtrim(file, "> "), WRONG_CHMOD), 0);
	}
	if (redir != NULL)
	{
		if (is_append(redir->content) == 2)
			fd = open(file, O_CREAT | O_RDWR, 0644);
		if (is_append(redir->content) == 1)
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			return (writing("cant open file", " "), 0);
		close(fd);
	}
	return (1);
}

t_token *last_redir(t_command *cmd)
{
	t_command	*tmp;
	t_token *the_one;

	tmp = cmd;
	the_one = NULL;
	while (tmp->redir != NULL)
	{
		if (tmp->redir->type == APPEND || tmp->redir->type == WRITE)
		{
			if (check_fd_out(tmp->redir) == 0)
				return (0);
			the_one = tmp->redir;
		}
		tmp->redir = tmp->redir->next;
	}
	return (the_one);
}

int	init_fd_out(t_command *cmd)
{
	t_token *redir;

	redir = last_redir(cmd);
	if (redir != NULL)
	{
		if (redir->type == APPEND)
			cmd->fd_out = opening_append(redir->content);
		if (redir->type == WRITE)
			cmd->fd_out = opening_standard_output(redir->content);
	}
	if (cmd->next != NULL)
		piping(cmd, redir->content);
	if (redir == NULL && cmd->next == NULL)
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
