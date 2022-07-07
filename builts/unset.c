/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:07:18 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/07 20:14:05 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void remove_env(char *name, t_env **env)
{
    t_env     *tmp;
    t_env     *ptr;

    tmp = (*env);
	ptr = tmp;
    if (tmp != NULL && ft_strcmp(name, tmp->name) == 0)
    {
        (*env) = tmp->next;
        free(tmp);
        tmp = (*env);
        ptr = (*env);
    }
    while (tmp != NULL)
    {    
        if (ft_strcmp(name, tmp->name) == 0)
        {
            ptr->next = tmp->next;
            free(tmp);
            tmp = ptr;
        }
        ptr = tmp;
        tmp = tmp->next;
    }
}

void	exec_unset(t_command *cmd)
{
	char *name;
	
	name = get_name(cmd->arg->argz[1]);
	remove_env(name, &cmd->env);
}
