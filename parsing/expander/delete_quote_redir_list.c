/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote_redir_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 22:44:21 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/31 00:21:08 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

int	del_all_neg_quotes_redir(t_command *cmd)
{
	t_token		*tmp;

	tmp = cmd->redir;
	while (tmp)
	{
		tmp->content = del_one_neg_quotes(tmp->content);
		if (!tmp->content)
			return (0);
		tmp = tmp->next;
	}
	replace_negativ_char_redir(cmd);
	return (1);
}

int	delete_quotes_redir_list(t_command *cmd)
{
    t_command   *tmp_cmd;
	t_token		*tmp_redir;

    tmp_cmd = cmd;
	while (tmp_cmd)
	{
        tmp_redir = tmp_cmd->redir;
		while (tmp_redir)
		{
			negativ_quote(tmp_redir->content);
			tmp_redir = tmp_redir->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
	if (!del_all_neg_quotes_redir(cmd))
		return (0);
	return (1);
}