/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execving.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:39:05 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 14:10:33 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	closing_next_fds(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	if (tmp->next != NULL)
	{
		if (cmd->next->fd_out != 1)
			close(cmd->next->fd_out);
		tmp = tmp->next;
	}
	tmp = tmp->next;
	while (tmp != NULL)
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
	}
}

void	forking(t_command *cmd)
{
	close(cmd->fd[0]);
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
	if (cmd->previous_fd != 0 && cmd->previous_fd != 1)
		close(cmd->previous_fd);
	closing_next_fds(cmd);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	if (execve(cmd->arg->path, cmd->arg->argz, cmd->envp_char) == -1)
		return ;
}

void	exec_token(t_command *cmd)
{
	cmd->envp_char = envp_to_char(cmd->env);
	cmd->arg->pid = fork();
	if (cmd->arg->pid == -1)
		return ;
	if (cmd->arg->pid == 0)
	{
		signal(SIGINT, exit_fork);
		forking(cmd);
	}
	else
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
	}
}
