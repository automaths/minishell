/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:02:09 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 17:05:17 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

static bool	check_quotes_one(char c, int *mode)
{
	if (c == '"' && *mode == NEUTRAL_MODE)
	{
		*mode = DQUOTE_MODE;
		return (0);
	}
	return (1);
}

static bool	check_quotes_two(char c, int *mode)
{
	if (c == '"' && *mode == DQUOTE_MODE)
	{
		*mode = NEUTRAL_MODE;
		return (0);
	}
	return (1);
}

static bool	check_quotes_three(char c, int *mode)
{
	if (c == '\'' && *mode == NEUTRAL_MODE)
	{
		*mode = SQUOTE_MODE;
		return (0);
	}
	return (1);
}

static bool	check_quotes_four(char c, int *mode)
{
	if (c == '\'' && *mode == SQUOTE_MODE)
	{
		*mode = NEUTRAL_MODE;
		return (0);
	}
	return (1);
}

bool	check_quotes(char *str)
{
	int	i;
	int	mode;

	i = -1;
	mode = NEUTRAL_MODE;
	while (str[++i])
	{
		while (1)
		{
			if (check_quotes_one(str[i], &mode) == 0)
				break ;
			if (check_quotes_two(str[i], &mode) == 0)
				break ;
			if (check_quotes_three(str[i], &mode) == 0)
				break ;
			if (check_quotes_four(str[i], &mode) == 0)
				break ;
			break ;
		}
	}
	if (mode == SQUOTE_MODE || mode == DQUOTE_MODE)
		return (0);
	return (1);
}
