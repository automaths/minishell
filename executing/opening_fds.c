/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:28:17 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 17:06:08 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../groshell.h"

int	opening_append(char *content, t_garbage **garbage)
{
	int	fd;

	content = ft_strtrim(content, "> ", garbage);
	if (access(content, F_OK) == 0)
	{
		if (access(content, W_OK) == -1)
			return (writing("can't write the file", " "), -1);
	}
	fd = open(content, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return (writing("cant open file", " "), -1);
	return (fd);
}

int	opening_standard_output(char *content, t_garbage **garbage)
{
	int	fd;

	content = ft_strtrim(content, "> ", garbage);
	if (access(content, F_OK) == 0)
	{
		if (access(content, W_OK) == -1)
			return (writing("can't write the file", " "), -1);
	}
	fd = open(content, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (writing("cant open file", " "), -1);
	return (fd);
}

int	opening_standard_input(char *content, t_garbage **garbage)
{
	int	fd;

	content = ft_strtrim(content, "< ", garbage);
	if (access(content, F_OK) == 0)
	{
		if (access(content, R_OK) == -1)
			return (writing("can't read the file", " "), -1);
	}
	fd = open(content, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return (writing("can't open the file", " "), -1);
	return (fd);
}
