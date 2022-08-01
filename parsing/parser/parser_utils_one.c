/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:47:12 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 14:50:45 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

void	add_redirection(t_first *tmp_uno, t_command *tmp_cmd, \
			t_garbage **garbage, int *t)
{
	if (tmp_uno->next != NULL && tmp_uno->next->type == WORD)
	{
		add_back_tkn(&tmp_cmd->redir \
			, new_tkn(ft_strjoin(tmp_uno->content \
				, tmp_uno->next->content, garbage), \
					tmp_uno->type, garbage));
		*t = 1;
	}
	else
		add_back_tkn(&tmp_cmd->redir \
			, new_tkn(tmp_uno->content, tmp_uno->type, garbage));
}

t_command	*add_pipe(t_command *tmp_cmd, t_env *env, t_garbage **garbage)
{
	add_back_cmd(&tmp_cmd, new_cmd(env, garbage));
	return (tmp_cmd->next);
}

t_first	*handling_the_t(t_first *tmp_uno, int *t)
{
	*t = 0;
	return (tmp_uno->next->next);
}

t_command	*step_two(t_first *uno, t_env *env, t_garbage **garbage)
{
	t_command		*cmd;
	t_command		*tmp_cmd;
	t_first			*tmp_uno;
	int				t;

	cmd = new_cmd(env, garbage);
	tmp_cmd = cmd;
	tmp_uno = uno;
	t = 0;
	while (tmp_uno != NULL)
	{
		if (tmp_uno->type == WORD)
			add_back_tkn(&tmp_cmd->arg \
				, new_tkn(tmp_uno->content, tmp_uno->type, garbage));
		if (tmp_uno->type == APPEND || tmp_uno->type == WRITE \
			|| tmp_uno->type == HEREDOC || tmp_uno->type == READ)
			add_redirection(tmp_uno, tmp_cmd, garbage, &t);
		if (tmp_uno->type == PIPE)
			tmp_cmd = add_pipe(tmp_cmd, env, garbage);
		if (t == 1)
			tmp_uno = handling_the_t(tmp_uno, &t);
		else
			tmp_uno = tmp_uno->next;
	}
	return (cmd);
}
