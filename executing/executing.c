/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:10:15 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/30 12:38:44 by nsartral         ###   ########.fr       */
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
		tmp = tmp->next;
		if (tmp == NULL)
			break ;
	}
	waitpiding(cmd);
	closing_fd(cmd);
	return (NULL);
}
	// return (tmp->env);
