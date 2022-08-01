/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:35:15 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 17:03:41 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../groshell.h"

int	singleton(int set, bool write)
{
	static int	singleton = 0;

	if (write)
		singleton = set;
	return (singleton);
}
