/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:47:12 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/30 15:40:14 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

t_command	*new_cmd(t_env *env)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (new == NULL)
		return (NULL);
	new->env = env;
	new->fd_in = -1;
	new->fd_out = -1;
	new->is_piped = 0;
	new->arg = NULL;
	new->redir = NULL;
	new->next = NULL;
	return (new);
}

void	add_back_cmd(t_command **cmd, t_command *new)
{
	t_command	*tmp;

	if (*cmd)
	{
		tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (cmd)
		*cmd = new;
}

t_token	*new_tkn(char *arg, int type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->content = arg;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_back_tkn(t_token **tkn, t_token *new)
{
	t_token	*tmp;

	if (*tkn)
	{
		tmp = *tkn;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (tkn)
		*tkn = new;
}

t_command	*step_two(t_first *uno, t_env *env)
{
	t_command		*cmd;
	t_command		*tmp_cmd;
	t_first			*tmp_uno;
	int				t;

	cmd = new_cmd(env);
	tmp_cmd = cmd;
	tmp_uno = uno;
	t = 0;
	while (tmp_uno != NULL)
	{
		if (tmp_uno->type == WORD)
			add_back_tkn(&tmp_cmd->arg \
				, new_tkn(tmp_uno->content, tmp_uno->type));
		if (tmp_uno->type == APPEND || tmp_uno->type == WRITE \
			|| tmp_uno->type == HEREDOC || tmp_uno->type == READ)
		{
			if (tmp_uno->next != NULL && tmp_uno->next->type == WORD)
			{
				add_back_tkn(&tmp_cmd->redir \
					, new_tkn(ft_strjoin(tmp_uno->content \
						, tmp_uno->next->content), tmp_uno->type));
				t = 1;
			}
			else
				add_back_tkn(&tmp_cmd->redir \
					, new_tkn(tmp_uno->content, tmp_uno->type));
		}
		if (tmp_uno->type == PIPE)
		{
			add_back_cmd(&tmp_cmd, new_cmd(env));
			tmp_cmd = tmp_cmd->next;
		}
		if (t == 1)
		{
			tmp_uno = tmp_uno->next->next;
			t = 0;
		}
		else
			tmp_uno = tmp_uno->next;
	}
	return (cmd);
}
