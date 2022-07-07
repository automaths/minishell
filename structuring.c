/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structuring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:28 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/07 12:45:33 by nimrod           ###   ########.fr       */
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

t_command	*parse_line(char *str, t_env *env)
{
	char			**split;
	t_command		*cmd;
	t_command		*tmp;
	int				i;

	split = spliting_plus(str);
	i = -1;
	cmd = new_cmd(i, env);
	tmp = cmd;
	while (split[++i])
	{
		if (is_arg(split[i]))
			add_back_tkn(&tmp->arg, new_tkn(split[i]));
		if (is_redirection(split[i]))
			add_back_tkn(&tmp->redir, new_tkn(split[i]));
		if (is_new_cmd(split[i]))
		{
			add_back_cmd(&tmp, new_cmd(i, env));
			tmp = tmp->next;
		}
	}
	return (cmd);
}
