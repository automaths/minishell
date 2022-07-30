/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:34:14 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/30 13:34:17 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	singleton(int set, bool write)
{
	static int	singleton = 0;

	if (write)
		singleton = set;
	return (singleton);
}
