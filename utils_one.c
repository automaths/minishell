/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:27:59 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/03 13:49:50 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	writing_error(char *str, int num)
{
	if (num == 1)
	{
		write(2, "bash: ", 6);
		if (str != NULL)
			write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 20);
	}
	if (num == 2)
	{
		write(2, "bash: ", 6);
		if (str != NULL)
			write(2, str, ft_strlen(str));
		write(2, ": no such file or directory\n",
			ft_strlen(": no such file or directory\n"));
	}
	if (num == 3)
	{
		write(2, "bash: ", 6);
		if (str != NULL)
			write(2, str, ft_strlen(str));
		write(2, ": permission denied\n", ft_strlen(": permission denied\n"));
	}
}

void	writing(char *intro, char *content)
{
	write(1, "\n", 1);
	write(1, intro, ft_strlen(intro));
	write(1, content, ft_strlen(content));
	write(1, "\n", 1);
}

void	print_fd(int fd)
{
	char	c;

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
