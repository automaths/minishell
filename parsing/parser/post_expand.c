/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 15:34:28 by nimrod            #+#    #+#             */
/*   Updated: 2022/08/03 19:43:51 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

bool	check_spliting(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			return (1);
		if (is_whitespace(str[i]))
			return (1);
	}
	return (0);
}

t_token	*update_argz(t_token *arg, t_garbage **garbage)
{
	t_token		*update;
	char		**split;
	int			i;

	update = NULL;
	split = ft_split(arg->content, ' ', garbage);
	i = -1;
	while (split[++i])
		add_back_tkn(&update, new_tkn(split[i], 0, garbage));
	return (update);
}

bool	two_words(char *str)
{
	int	i;
	int	t;

	i = -1;
	t = 0;
	while (is_whitespace(str[++i]))
		;
	while (str[i++])
	{
		if (str[i] == ' ' || str[i] == '/')
			t = 1;
		if (t == 1 && (str[i] >= 33 && str[i] <= 126))
			return (1);
	}
	return (0);
}

void	spliting_quotes(t_command *cmd)
{
	t_command	*tmp;
	t_token		*tnp;
	t_token		*top;

	tmp = cmd;
	while (tmp != NULL)
	{
		if (tmp->arg)
		{
			if (check_spliting(tmp->arg->content) \
				&& two_words(tmp->arg->content))
			{
				tnp = tmp->arg->next;
				tmp->arg = update_argz(tmp->arg, cmd->garbage);
				top = tmp->arg;
				while (top != NULL)
					top = top->next;
				top = tnp;
			}
		}
		tmp = tmp->next;
	}
}
