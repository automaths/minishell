/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:27:59 by nsartral          #+#    #+#             */
/*   Updated: 2022/06/27 20:01:02 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	writing(char *intro, char *content)
{
	write(1, "\n", 1);
	write(1, intro, ft_strlen(intro));
	write(1, content, ft_strlen(content));
	write(1, "\n", 1);
}

void	print_fd(int fd)
{
	char c;
	
	c = fd + '0';
	write(1, "the fd is :", 11);
	write(1, &c, 1);
	write(1, "\n", 1);
}

int	is_heredoc(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '<')
			++j;
	}
	if (j == 2)
		return (2);
	if (j == 1)
		return (1);
	return (0);
}

int	is_append(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '>')
			++j;
	}
	if (j == 2)
		return (2);
	if (j == 1)
		return (1);
	return (0);
}
