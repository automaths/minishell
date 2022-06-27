/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:06:53 by nsartral          #+#    #+#             */
/*   Updated: 2022/06/27 12:09:54 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool	cd(char *arg)
{
	int		fd;
	char	*pwdz;
	char	*path;

	pwdz = NULL;
	pwdz = getcwd(pwdz, 4096);
	fd = open(arg, __O_DIRECTORY);
	if (fd == -1)
		return (printf("\n%s is not a directory", arg), 0);
	close(fd);
	path = ft_strjoin(pwdz, "/");
	path = ft_strjoin(path, arg);
	chdir(path);
	return (1);
}
