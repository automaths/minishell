/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:10:15 by nsartral          #+#    #+#             */
/*   Updated: 2022/06/27 20:12:16 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	forking(t_command *cmd)
{
	if (cmd->fd_in != 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return ;
	}
	if (cmd->fd_out != 1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return ;
	}
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	if (execve(cmd->arg->path, cmd->arg->argz, cmd->arg->envp) == -1)
		return ;
}

void	exec_token(t_command *cmd)
{
	cmd->arg->pid = fork();
	if (cmd->arg->pid == -1)
		return ;
	if (cmd->arg->pid == 0)
		forking(cmd);
	else
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
	}
}

void	closing_fd(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		if (tmp->fd_in != 0 && tmp->fd_in != 1)
			close(tmp->fd_in);
		if (tmp->fd_out != 0 && tmp->fd_out != 1)
			close(tmp->fd_out);
		tmp = tmp->next;
	}
}

void	waitpiding(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		waitpid(tmp->arg->pid, 0, 0);
		tmp = tmp->next;
	}
}

bool	exec_command(t_command *cmd, char **envp)
{
	t_command	*tmp;

	if (!cmd)
		return (0);
	tmp = cmd;
	redirectionning(tmp);
	while (tmp != NULL)
	{
		if (parse_argument(tmp->arg, envp) == 0)
			return(perror("oups"), 0);
		print_fd(tmp->fd_in);
		print_fd(tmp->fd_out);
		exec_token(tmp);
		tmp = tmp->next;
		if (tmp == NULL)
			break ;
	}
	waitpiding(cmd);
	closing_fd(cmd);
	return (1);
}
