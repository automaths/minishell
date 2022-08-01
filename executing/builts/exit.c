/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:07:06 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 17:06:57 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

bool	is_exit(char c)
{
	if (c == 'e' || c == 'x' || c == 'i' || c == 't')
		return (1);
	return (0);
}

int	find_exit_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_whitespace(str[i]))
		i++;
	while (str[i] && is_exit(str[i]))
		i++;
	while (str[i] && is_whitespace(str[i]))
		i++;
	if (!str[i] || str[i] < '0' || str[i] > '9')
		return (0);
	if (str[i])
		return (ft_atoi(&str[i]));
	return (0);
}

void	exec_exit(t_command *cmd)
{
	int	n;

	n = find_exit_number(cmd->arg->argz[0]);
	exit(n);
}
