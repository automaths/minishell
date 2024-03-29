/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:07:02 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 17:07:00 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

void	exec_env(t_command *cmd)
{
	t_env	*tmp;

	tmp = cmd->env;
	while (tmp != NULL)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, "=", 1);
		write(1, tmp->content, ft_strlen(tmp->content));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}
