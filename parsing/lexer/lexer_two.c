/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:43:59 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 12:12:56 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

int	lexer_id_four_one(char c, int *j, int *mode)
{
	if (c == '"' && *mode == DQUOTE_MODE)
	{
		*j = *j + 1;
		*mode = NEUTRAL_MODE;
		return (0);
	}
	return (1);
}

int	lexer_id_four_two(char c, int *j, int *mode)
{
	if (c == '\'' && *mode == SQUOTE_MODE)
	{
		*j = *j + 1;
		*mode = NEUTRAL_MODE;
		return (0);
	}
	return (1);
}

int	lexer_id_five(char *str, int *mode, int *i)
{
	int	j;

	j = 0;
	while (str[*i + ++j] && (*mode == WORD_MODE || *mode == SQUOTE_MODE \
		|| *mode == DQUOTE_MODE))
	{
		if ((actual_mode(str[*i + j]) != WORD_MODE) && (*mode == WORD_MODE))
		{
			*mode = NEUTRAL_MODE;
			break ;
		}
		if (lexer_id_four_one(str[*i + j], &j, mode) == 0)
			break ;
		if (lexer_id_four_two(str[*i + j], &j, mode) == 0)
			break ;
		if (!str[*i + j + 1])
		{
			*mode = NEUTRAL_MODE;
			j++;
			break ;
		}
	}
	// add_back_uno(uno, new_uno(WORD, alloc_content(&str[*i], j, garbage), garbage));
	// *i = *i + j - 1;
	return (j);
}

int	lexer_id_four(t_first **uno, char *str, int *mode, int *i, t_garbage **garbage)
{
	int j;

	if (str[*i] == '"')
		*mode = DQUOTE_MODE;
	else if (str[*i] == '\'')
		*mode = SQUOTE_MODE;
	else
		*mode = WORD_MODE;
	j = lexer_id_five(str, mode, i);
	add_back_uno(uno, new_uno(WORD, alloc_content(&str[*i], j, garbage), garbage));
	*i = *i + j - 1;
	return (1);
}
