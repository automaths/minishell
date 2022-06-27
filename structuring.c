/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structuring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:28 by nsartral          #+#    #+#             */
/*   Updated: 2022/06/27 12:30:48 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_command	*parse_line(char *str)
{
	char			**split;
	char			*str_quoted;
	t_command		*cmd;
	t_command		*tmp;
	int				i;

	str_quoted = quoting_ruling(str);
	split = ft_split(str_quoted, ' ');
	if (split == NULL)
		return (NULL);
	split = split_cleaning(split);
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
