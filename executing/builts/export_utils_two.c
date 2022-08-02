/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:00:08 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/02 15:32:40 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

void	export_shlvl(t_command *cmd, bool add)
{
	int		shlvl;
	char	*content;

	shlvl = ft_atoi(find_content_cd("SHLVL", cmd->env));
	if (add)
		shlvl++;
	else
		shlvl--;
	content = ft_itoa(shlvl, cmd->garbage);
	update_env("SHLVL", content, cmd->env);
}

void	print_export(t_command *cmd)
{
	t_env	*tmp;

	tmp = cmd->env;
	while (tmp != NULL)
	{
		write (1, "declare -x ", ft_strlen("declare -x "));
		write (1, tmp->name, ft_strlen(tmp->name));
		write (1, "=", 1);
		write (1, tmp->content, ft_strlen(tmp->content));
		write (1, "\n", 1);
		tmp = tmp->next;
	}
}
