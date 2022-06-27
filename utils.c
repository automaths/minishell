/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:27:59 by nsartral          #+#    #+#             */
/*   Updated: 2022/06/27 12:33:34 by nsartral         ###   ########.fr       */
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
