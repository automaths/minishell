/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:43:40 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/31 16:41:10 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

int	lexer_id_one(char c, int *mode)
{
	if (c == ' ' || c == ';')
		return (0);
	if (c == '>' && *mode == NEUTRAL_MODE)
	{
		*mode = R_REDIR_MODE;
		return (0);
	}
	if (c == '<' && *mode == NEUTRAL_MODE)
	{
		*mode = L_REDIR_MODE;
		return (0);
	}
	return (1);
}

int	lexer_id_two(t_first **uno, char *str, int *mode, t_garbage **garbage)
{
	int	i;

	i = 1;
	if (*mode == R_REDIR_MODE && str[i] == '>')
	{
		add_back_uno(uno, new_uno(APPEND, alloc_content(&str[i - 1], 2), garbage));
		*mode = NEUTRAL_MODE;
		return (0);
	}
	if (*mode == R_REDIR_MODE && str[i] != '>')
	{
		add_back_uno(uno, new_uno(WRITE, alloc_content(&str[i - 1], 1), garbage));
		*mode = actual_mode(str[i]);
	}
	return (1);
}

int	lexer_id_three(t_first **uno, char *str, int *mode, t_garbage **garbage)
{
	int	i;

	i = 1;
	if (*mode == L_REDIR_MODE && str[i] == '<')
	{
		add_back_uno(uno, new_uno(HEREDOC, alloc_content(&str[i - 1], 2), garbage));
		*mode = NEUTRAL_MODE;
		return (0);
	}
	if (*mode == L_REDIR_MODE && str[i] != '<')
	{
		add_back_uno(uno, new_uno(READ, alloc_content(&str[i - 1], 1), garbage));
		*mode = actual_mode(str[i]);
	}
	if (str[i] == '|')
	{
		add_back_uno(uno, new_uno(PIPE, alloc_content(&str[i], 1), garbage));
		return (0);
	}
	return (1);
}

t_first	*lexer(char *str, t_garbage **garbage)
{
	t_first		*uno;
	int			mode;
	int			i;

	(void)garbage;
	if (check_quotes(str) == 0)
		return (write(1, "Error, quotes not ended\n", 31), NULL);
	mode = NEUTRAL_MODE;
	uno = new_uno(7, "start of chained list", garbage);
	i = -1;
	while (str[++i])
	{
		while (1)
		{
			if (lexer_id_one(str[i], &mode) == 0)
				break ;
			if (lexer_id_two(&uno, &str[i - 1], &mode, garbage) == 0)
				break ;
			if (lexer_id_three(&uno, &str[i - 1], &mode, garbage) == 0)
				break ;
			if (lexer_id_four(&uno, str, &mode, &i, garbage) == 0)
				break ;
			break ;
		}
	}
	return (uno);
}
