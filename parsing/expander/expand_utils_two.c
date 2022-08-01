/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:27:07 by jucheval          #+#    #+#             */
/*   Updated: 2022/08/01 20:30:40 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

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

void	parse_dollars_redir(t_command *cmd)
{
	int			i;
	int			quote;
	t_command	*tmp;
	t_token		*tmp_redir;

	quote = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp_redir = tmp->redir;
		while (tmp_redir)
		{
			i = 0;
			while (tmp_redir->content[i])
			{
				quote = what_state(tmp_redir->content, i);
				if (tmp_redir->content[i] == '$' && quote == 1)
					tmp_redir->content[i] *= -1;
				i++;
			}
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
}
