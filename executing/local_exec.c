/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 22:21:35 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/31 00:11:10 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool	check_local_exec(char *command)
{
	int	i;

	i = -1;
	while (command[++i] && is_whitespace2(command[i]))
		;
	if (command[i] && command[i] == '.' && command[i + 1] \
		&& command[i + 1] == '/' && command[i + 2] \
		&& is_printable_except_space(command[i + 2]))
		return (1);
	return (0);
}

void	local_forking(t_command *cmd)
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
	if (execve(cmd->arg->command, cmd->arg->argz, cmd->envp_char) == -1)
		return ;
}

void	error_local_exec(t_command *cmd)
{
	singleton(127, 1);
	write(2, "bash: ", 6);
	write(2, cmd->arg->command, ft_strlen(cmd->arg->command));
	write(2, ": No such file or directory\n"\
		, ft_strlen(": No such file or directory\n"));
}

void	local_exec(t_command *cmd)
{
	char	**exec;

	cmd->envp_char = envp_to_char(cmd->env);
	if (access(cmd->arg->command, F_OK | X_OK) != 0)
	{
		error_local_exec(cmd);
		return ;
	}
	exec = (char **)malloc(sizeof(char *) * 2);
	exec[0] = cmd->arg->command;
	exec[1] = NULL;
	cmd->arg->argz = exec;
	cmd->arg->pid = fork();
	if (cmd->arg->pid == -1)
		return ;
	if (cmd->arg->pid == 0)
		local_forking(cmd);
	else
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
	}
}
