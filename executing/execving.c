/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execving.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:39:05 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/31 23:16:32 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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
		// if (cmd->fd[1] != 0)
		// 	close(cmd->fd[1]);
	}
}
