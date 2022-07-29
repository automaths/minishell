/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:47:24 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/29 15:47:25 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool	is_whitespace(char c)
{
	if (c == ' ' && c == '\t' && c == '\v'
		&& c == '\n' && c == '\r' && c == '\f')
		return (1);
	return (0);
}

bool	is_whitespace2(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\n' || c == '\r' || c == '\f')
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
