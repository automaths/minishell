/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:39:36 by nimrod            #+#    #+#             */
/*   Updated: 2022/07/03 13:40:22 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	is_whitespace(char c)
{
	if (c == ' ' && c == '\t' && c == '\v'
		&& c == '\n' && c == '\r' && c == '\f')
		return (1);
	return (0);
}

bool	is_lowercase(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

bool	is_printable_except_space(char c)
{
	if (c < 33 || c > 126)
		return (0);
	return (1);
}
