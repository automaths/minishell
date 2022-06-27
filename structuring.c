/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structuring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:28 by nsartral          #+#    #+#             */
/*   Updated: 2022/06/27 13:56:06 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**spliting_plus(char *str)
{
	char	*str_quoted;
	char	**split;

	str_quoted = quoting_ruling(str);
	split = ft_split(str_quoted, ' ');
	if (split == NULL)
		return (NULL);
	split = split_cleaning(split);
	return (split);
}

t_command	*parse_line(char *str)
{
	char			**split;
	t_command		*cmd;
	t_command		*tmp;
	int				i;

	split = spliting_plus(str);
	i = -1;
	cmd = new_cmd(i);
	tmp = cmd;
	while (split[++i])
	{
		if (is_arg(split[i]))
			add_back_tkn(&tmp->arg, new_tkn(split[i]));
		if (is_redirection(split[i]))
			add_back_tkn(&tmp->redir, new_tkn(split[i]));
		if (is_new_cmd(split[i]))
		{
			add_back_cmd(&tmp, new_cmd(i));
			tmp = tmp->next;
		}
	}
	return (cmd);
}
