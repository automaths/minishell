/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:10:15 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 12:56:27 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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

void	updating_singleton(int num)
{
	if (num == 512)
		singleton(2, 1);
	else if (num == 256)
		singleton(1, 1);
	else if (num == 127)
		singleton(127, 1);
	else if (num == 32512)
		singleton(127, 1);
	else if (num == 0)
		singleton(0, 1);
}

void	waitpiding(t_command *cmd)
{
	t_command	*tmp;
	int			num;

	tmp = cmd;
	while (tmp != NULL)
	{
		if (tmp->arg != NULL)
		{
			if (waitpid(tmp->arg->pid, &num, 2) != -1)
			{
				if (tmp->arg->pid && num)
					updating_singleton(num);
			}
		}
		tmp = tmp->next;
	}
}

void	launching_execution(t_command *cmd)
{
	if (check_local_exec(cmd->arg->argz[0]))
		local_exec(cmd);
	else if (check_builts(cmd->arg->argz))
	{
		if (check_builts_nofork(cmd->arg->argz))
			exec_token_builts_nofork(cmd);
		else
			exec_token_builts(cmd);
	}
	else
		exec_token(cmd);
}

t_env	*exec_command(t_command *cmd)
{
	t_command	*tmp;

	if (!cmd)
		return (NULL);
	tmp = cmd;
	if (redirectionning(tmp) == 0)
		return (NULL);
	while (tmp != NULL)
	{
		if (parse_argument(tmp) == 0)
		{
			if (tmp != NULL && tmp->next != NULL)
				tmp->next->fd_in = -1;
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			launching_execution(tmp);
		}
		tmp = tmp->next;
	}
	waitpiding(cmd);
	signal(SIGINT, prompt_signal);
	closing_fd(cmd);
	return (NULL);
}
