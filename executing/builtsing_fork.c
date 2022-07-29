/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsing_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:39:24 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/29 15:39:35 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool	check_builts(char **argz)
{
	if (ft_strncmp("echo", argz[0], 5) == 0)
		return (1);
	if (ft_strncmp("env", argz[0], 4) == 0)
		return (1);
	if (ft_strncmp("pwd", argz[0], 4) == 0)
		return (1);
	if (ft_strncmp("export", argz[0], 7) == 0)
		return (1);
	if (ft_strncmp("unset", argz[0], 6) == 0)
		return (1);
	if (ft_strncmp("cd", argz[0], 3) == 0)
		return (1);
	if (ft_strncmp("exit", argz[0], 5) == 0)
		return (1);
	return (0);
}

void	exec_builts(t_command *cmd)
{
	if (ft_strncmp(cmd->arg->argz[0], "echo", 5) == 0)
		exec_echo(cmd);
	if (ft_strncmp(cmd->arg->argz[0], "pwd", 4) == 0)
		exec_pwd(cmd);
	if (ft_strncmp(cmd->arg->argz[0], "env", 4) == 0)
		exec_env(cmd);
	exit(0);
}

void	forking_builts(t_command *cmd)
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
	exec_builts(cmd);
}

void	exec_token_builts(t_command *cmd)
{
	cmd->arg->pid = fork();
	if (cmd->arg->pid == -1)
		return ;
	if (cmd->arg->pid == 0)
		forking_builts(cmd);
	else
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
	}
}
