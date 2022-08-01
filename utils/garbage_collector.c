/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:24:02 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 17:04:01 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../groshell.h"

void	init_garbage(t_garbage **garbage)
{
	(*garbage)->s_char = NULL;
	(*garbage)->d_char = NULL;
	(*garbage)->fst = NULL;
	(*garbage)->cmd = NULL;
	(*garbage)->tkn = NULL;
	(*garbage)->env = NULL;
}

t_garbage	*new_garbage(void *content, int type)
{
	t_garbage	*new;

	new = (t_garbage *)malloc(sizeof(t_garbage));
	if (new == NULL)
		return (NULL);
	init_garbage(&new);
	if (type == S_CHAR)
		new->s_char = (char *)content;
	if (type == D_CHAR)
		new->d_char = (char **)content;
	if (type == FST)
		new->fst = (t_first *)content;
	if (type == CMD)
		new->cmd = (t_command *)content;
	if (type == TKN)
		new->tkn = (t_token *)content;
	if (type == ENV)
		new->env = (t_env *)content;
	new->next = NULL;
	return (new);
}

void	add_garbage(t_garbage **grb, t_garbage *new)
{
	t_garbage	*tmp;

	if (*grb)
	{
		tmp = *grb;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (grb)
		*grb = new;
}

void	clean_garbage(t_garbage **grb)
{
	t_garbage	*tmp;
	t_garbage	*next;

	tmp = *grb;
	while (tmp)
	{
		next = tmp->next;
		if ((tmp)->d_char != NULL)
			free((tmp)->d_char);
		if ((tmp)->s_char != NULL)
			free((tmp)->s_char);
		if ((tmp)->fst != NULL)
			free((tmp)->fst);
		if ((tmp)->cmd != NULL)
			free((tmp)->cmd);
		if ((tmp)->tkn != NULL)
			free((tmp)->tkn);
		if ((tmp)->env != NULL)
			free((tmp)->env);
		free(tmp);
		tmp = next;
	}
	*grb = NULL;
}
