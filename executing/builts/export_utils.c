/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:37:21 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/29 15:37:26 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

bool	is_export(char c)
{
	if (c == 'e' || c == 'x' || c == 'p' || c == 'o' \
			|| c == 'r' || c == 't')
		return (1);
	return (0);
}

bool	check_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (1);
	}
	return (0);
}

void	add_back_env(char *name, char *content, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (tmp == NULL)
		return ;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_lst(name, content);
}

void	read_envz(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, "=", 1);
		write(1, tmp->content, ft_strlen(tmp->content));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

void	update_all_envz(t_command *cmd, t_env *env)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		tmp->env = env;
		tmp = tmp->next;
	}
}
