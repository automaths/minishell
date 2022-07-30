/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:10:15 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/30 14:50:21 by nsartral         ###   ########.fr       */
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

void	waitpiding(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		if (tmp->arg != NULL)
			waitpid(tmp->arg->pid, 0, 0);
		tmp = tmp->next;
	}
}

void	launching_execution(t_command *cmd)
{
	if (check_builts(cmd->arg->argz))
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
			launching_execution(tmp);
		tmp = tmp->next;
	}
	waitpiding(cmd);
	closing_fd(cmd);
	return (NULL);
}
