/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsing_nofork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:34:24 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/29 17:34:44 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool	check_builts_nofork(char **argz)
{
	if (ft_strncmp(argz[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(argz[0], "unset", 6) == 0)
		return (1);
	if (ft_strncmp(argz[0], "exit", 5) == 0)
		return (1);
	if (ft_strncmp(argz[0], "cd", 3) == 0)
		return (1);
	return (0);
}

void	exec_token_builts_nofork(t_command *cmd)
{
	if (ft_strncmp(cmd->arg->argz[0], "export", 7) == 0)
		exec_export(cmd);
	if (ft_strncmp(cmd->arg->argz[0], "unset", 6) == 0)
		exec_unset(cmd);
	if (ft_strncmp(cmd->arg->argz[0], "exit", 5) == 0)
		exec_exit(cmd);
	if (ft_strncmp(cmd->arg->argz[0], "cd", 3) == 0)
		exec_cd(cmd);
}
