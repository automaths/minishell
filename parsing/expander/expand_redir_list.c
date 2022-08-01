/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 22:37:39 by jucheval          #+#    #+#             */
/*   Updated: 2022/08/01 11:46:50 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

int	delete_redir_char_in_redir_list(t_command *cmd)
{
	t_command	*tmp;
	t_token		*tmp_redir;

	tmp = cmd;
	while (tmp)
	{
		tmp_redir = tmp->redir;
		while (tmp_redir)
		{
			tmp_redir->content = ft_strtrim(tmp_redir->content, "<>", cmd->garbage);
			if (!tmp_redir->content)
				return (0);
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	replace_variable_redir(t_command *cmd, t_env *env)
{
	int			i;
	t_command	*tmp;
	t_token		*tmp_redir;

	tmp = cmd;
	while (tmp)
	{
		tmp_redir = tmp->redir;
		while (tmp_redir)
		{
			i = -1;
			while (tmp_redir->content[++i])
			{
				if (tmp_redir->content[i] == '$')
				{
					tmp_redir->content = \
					replace_one_variable(tmp_redir->content, env, i, cmd);
					if (!tmp_redir->content)
						return (0);
				}
			}
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
	return (1);
}
