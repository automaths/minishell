/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:48:07 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 22:53:25 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

t_command	*new_cmd(t_env *env, t_garbage **garbage)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (new == NULL)
		return (exiting_malloc(garbage), NULL);
	add_garbage(garbage, new_garbage(new, CMD));
	new->env = env;
	new->fd_in = -1;
	new->fd_out = -1;
	new->previous_fd = -1;
	new->is_piped = 0;
	new->is_piping = 0;
	new->is_exec = 0;
	new->arg = NULL;
	new->redir = NULL;
	new->next = NULL;
	new->garbage = garbage;
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

t_token	*new_tkn(char *arg, int type, t_garbage **garbage)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (exiting_malloc(garbage), NULL);
	add_garbage(garbage, new_garbage(new, TKN));
	new->content = arg;
	new->type = type;
	new->garbage = garbage;
	new->pid = 0;
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
