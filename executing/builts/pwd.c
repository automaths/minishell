/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:07:14 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 17:06:44 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

char	*find_pwd(t_command *cmd)
{
	t_env	*tmp;

	tmp = cmd->env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void	exec_pwd(t_command *cmd)
{
	char	*path;

	path = find_pwd(cmd);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
}
