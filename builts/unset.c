/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:07:18 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/07 19:07:05 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// void remove_env(char *name, t_list **env)
// {
//     t_list     *tmp;
//     t_list     *ptr;

//     tmp = (*env);
// 	ptr = tmp;
//     if (tmp != NULL && ft_strcmp(name, tmp->name) == 0)
//     {
//         (*env) = tmp->next;
//         free(tmp);
//         tmp = (*env);
//         ptr = (*env);
//     }
//     while (tmp != NULL)
//     {    
//         if (ft_strcmp(name, tmp->name) == 0)
//         {
//             ptr->next = tmp->next;
//             free(tmp);
//             tmp = ptr;
//         }
//         ptr = tmp;
//         tmp = tmp->next;
//     }
// }

// void	exec_unset(char *str, t_list *env)
// {
// 	char *name;
	
// 	name = get_name(str);
// 	remove_env(name, &env);
// }

void	exec_unset(t_command *cmd)
{
	(void)cmd;
}
