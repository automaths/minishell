/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:00:08 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 17:06:50 by nsartral         ###   ########.fr       */
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
