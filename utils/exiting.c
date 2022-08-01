/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:30:46 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 17:19:50 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../groshell.h"

void	exiting(char *str, t_garbage **garbage)
{
	if (str != NULL)
	{
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	clean_garbage(garbage);
	exit(singleton(0, 0));
}
