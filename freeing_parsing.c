/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:20:42 by nsartral          #+#    #+#             */
/*   Updated: 2022/06/27 12:20:44 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

	// int	i;
	// i = -1;
	// while (arg->unix_paths[++i])
	// 	free(arg->unix_paths[i]);
	// if (arg->unix_paths)
	// 	free(arg->unix_paths);
void	freeing_unix(t_token *arg)
{
	(void)arg;
}

	// if (arg->command)
	// 	free(arg->command);
void	freeing_command(t_token *arg)
{
	(void)arg;
}

	// if (arg->path)
	// 	free(arg->path);
void	freeing_path(t_token *arg)
{
	(void)arg;
}

	// int	i;
	// i = -1;
	// while (arg->argz[++i])
	// 	free(arg->argz[i]);
	// if (arg->argz)
	// 	free(arg->argz);
void	freeing_argz(t_token *arg)
{
	(void)arg;
}

	// freeing_argz(arg);
	// freeing_path(arg);
void	freeing_path_and_argz(t_token *arg)
{
	(void)arg;
}
