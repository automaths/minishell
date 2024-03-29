/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:37:18 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/03 18:17:47 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../groshell.h"

void	writing_error(char *str, int num)
{
	if (num == 1)
	{
		write(2, "groshell: ", 10);
		if (str != NULL)
			write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 20);
	}
	if (num == 2)
	{
		write(2, "groshell: ", 10);
		if (str != NULL)
			write(2, str, ft_strlen(str));
		write(2, ": no such file or directory\n",
			ft_strlen(": no such file or directory\n"));
	}
	if (num == 3)
	{
		write(2, "groshell: ", 10);
		if (str != NULL)
			write(2, str, ft_strlen(str));
		write(2, ": permission denied\n", ft_strlen(": permission denied\n"));
	}
}

void	writing(char *intro, char *content)
{
	write(1, intro, ft_strlen(intro));
	write(1, content, ft_strlen(content));
}
