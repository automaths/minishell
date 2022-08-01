/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:20:54 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 17:06:41 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

void	remove_env(char *name, t_env **env)
{
	t_env	*tmp;
	t_env	*ptr;

	tmp = (*env);
	ptr = tmp;
	if (tmp != NULL && ft_strcmp(name, tmp->name) == 0)
	{
		(*env) = tmp->next;
		tmp = (*env);
		ptr = (*env);
	}
	while (tmp != NULL)
	{	
		if (ft_strcmp(name, tmp->name) == 0)
		{
			ptr->next = tmp->next;
			tmp = ptr;
		}
		ptr = tmp;
		tmp = tmp->next;
	}
}

void	exec_unset(t_command *cmd)
{
	char	*name;

	if (cmd->arg->argz[1] == NULL)
		return ;
	name = get_name(cmd->arg->argz[1], cmd->garbage);
	remove_env(name, &cmd->env);
}
