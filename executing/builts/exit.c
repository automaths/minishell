/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:07:06 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/02 15:34:01 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

bool	is_exit(char c)
{
	if (c == 'e' || c == 'x' || c == 'i' || c == 't')
		return (1);
	return (0);
}

bool	check_first(char *str)
{
	int			i;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (!str[i] || !(str[i] >= '0' && str[i] <= '9'))
		return (0);
	return (1);
}

void	exiting_exit(int n, t_command *cmd, bool correct)
{
	if (correct)
	{
		clean_garbage(cmd->garbage);
		write(1, "exit\n", ft_strlen("exit\n"));
		exit(n);
	}
	if (!correct)
	{
		write(1, "bash: exit: ", ft_strlen("bash: exit: "));
		write(1, cmd->arg->argz[1], ft_strlen(cmd->arg->argz[1]));
		write(1, ": numeric argument required\n", \
			ft_strlen(": numeric argument required:\n"));
		clean_garbage(cmd->garbage);
		exit(2);
	}
}

void	exec_exit(t_command *cmd)
{
	int	n;

	if (cmd->arg->argz[1] == NULL)
	{
		if (!cmd->next)
			exiting_exit(0, cmd, 1);
		return ;
	}
	if (!check_first(cmd->arg->argz[1]))
	{
		if (!cmd->next)
			exiting_exit(2, cmd, 0);
		return ;
	}
	n = ft_atoi(cmd->arg->argz[1]);
	if (!cmd->next)
		exiting_exit(n, cmd, 1);
	return ;
}
