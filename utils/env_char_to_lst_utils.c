/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_char_to_lst_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:37:05 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/31 19:18:09 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_env	*new_lst(char *name, char *content, t_garbage **garbage)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	add_garbage(garbage, new_garbage(new, ENV));
	new->name = name;
	new->content = content;
	new->garbage = garbage;
	new->next = NULL;
	return (new);
}

void	add_back_lst(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (lst)
		*lst = new;
}

int	has_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
	}
	return (0);
}

bool	check_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (has_equal(envp[i]) < 1)
			return (printf("wrong env variable"), 0);
	}
	return (1);
}
