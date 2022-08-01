/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:30:46 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 18:14:18 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../groshell.h"

void	exiting_malloc(t_garbage **garbage)
{
	write(1, "malloc error exit", ft_strlen("malloc error exit"));
	write(1, "\n", 1);
	clean_garbage(garbage);
	exit(1);
}
