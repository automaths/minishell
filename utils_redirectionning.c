/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirectionning_one.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:28:22 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/03 13:36:51 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
