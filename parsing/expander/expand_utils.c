/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 21:50:02 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/29 14:32:38 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

void	replace_negativ_char(t_command *cmd)
{
	int			i;
	t_command	*tmp;
	t_token		*tmp_token;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp_token = tmp->arg;
		while (tmp_token)
		{
			i = 0;
			while (tmp_token->content[i])
			{
				if (tmp_token->content[i] < 0)
					tmp_token->content[i] *= -1;
				i++;
			}
			tmp_token = tmp_token->next;
		}
		tmp = tmp->next;
	}
}

int	ft_isalnum(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90)
		|| (c >= 48 && c <= 57) || (c == '$'))
		return (1);
	return (0);
}

int	what_state(char *str, int j)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (i <= j)
	{
		if (str[i] == '\'' && quote == 1)
			quote = 0;
		else if (str[i] == '\'' && quote == 0)
			quote = 1;
		if (str[i] == '\"' && quote == 2)
			quote = 0;
		else if (str[i] == '\"' && quote == 0)
			quote = 2;
		i++;
	}
	return (quote);
}

void	parse_dollars(t_command *cmd)
{
	int			i;
	int			quote;
	t_command	*tmp;
	t_token		*tmp_arg;

	quote = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp_arg = tmp->arg;
		while (tmp_arg)
		{
			i = 0;
			while (tmp_arg->content[i])
			{
				quote = what_state(tmp_arg->content, i);
				if (tmp_arg->content[i] == '$' && quote == 1)
					tmp_arg->content[i] *= -1;
				i++;
			}
			tmp_arg = tmp_arg->next;
		}
		tmp = tmp->next;
	}
}
