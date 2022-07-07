/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:10:15 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/07 13:58:03 by nimrod           ###   ########.fr       */
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
	if (execve(cmd->arg->path, cmd->arg->argz, cmd->arg->envp_char) == -1)
		return ;
}

void	exec_token(t_command *cmd)
{
	cmd->arg->envp_char = envp_to_char(cmd->arg->envp);
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

bool	check_builts_nofork(char **argz)
{
	if (ft_strncmp(argz[0], "export", 7) == 0)
	{
		write(1, "nofork", 6);
		return (1);
	}
	return (0);
}

void	exec_token_builts_nofork(t_command *cmd)
{
	if (ft_strncmp(cmd->arg->argz[0], "export", 7) == 0)
		exec_export(cmd);
}

t_env	*exec_command(t_command *cmd, t_env *envp)
{
	t_command	*tmp;

	if (!cmd)
		return (NULL);
	tmp = cmd;
	if (redirectionning(tmp) == 0)
		return (NULL);
	while (tmp != NULL)
	{
		if (parse_argument(tmp->arg, envp) == 0)
		{
			if (tmp->next != NULL)
				tmp->next->fd_in = -1;
		}
		else
		{
			if (check_builts(tmp->arg->argz))
			{
				if (check_builts_nofork(tmp->arg->argz))
					exec_token_builts_nofork(tmp);
				else
					exec_token_builts(tmp);
			}
			else
				exec_token(tmp);
		}
		// read_envz(tmp->env);
		print_fd(tmp->fd_in);
		print_fd(tmp->fd_out);
		tmp = tmp->next;
		if (tmp == NULL)
			break ;
	}
	waitpiding(cmd);
	closing_fd(cmd);
	tmp = cmd;
	while (tmp->next != NULL)
		tmp = tmp->next;
	// read_envz(tmp->env);
	return (tmp->env);
}
