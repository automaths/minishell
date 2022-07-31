/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:24:02 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/31 16:47:14 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	updator_next(t_command *cmd)
{
	t_command *tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		tmp->garbage = cmd->garbage;
		tmp = tmp->next;
	}
}

void	updator_all(t_command *cmd)
{
	t_command *tmp;
	t_command *tnp;

	tmp = cmd;
	while(tmp->next != NULL)
		tmp = tmp->next;
	tnp = cmd;
	while (tnp != NULL)
	{
		tnp->garbage = tmp->garbage;
		tnp = tnp->next;
	}
}

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
	int			i;

	tmp = *grb;
	while (tmp)
	{
		next = tmp->next;
		if ((tmp)->d_char != NULL)
		{
			write(1, "freeing d_char	", ft_strlen("freeing d_char	"));
			i = -1;
			while ((tmp)->d_char[++i] != NULL)
			{
				free((tmp)->d_char[i]);
			}
			free((tmp)->d_char);
		}
		if ((tmp)->s_char != NULL)
		{
			write(1, "freeing s_char	", ft_strlen("freeing s_char	"));
			free((tmp)->s_char);
		}
		if ((tmp)->fst != NULL)
		{
			write(1, "freeing fst	", ft_strlen("freeing fst	"));
			free((tmp)->fst);
		}
		if ((tmp)->cmd != NULL)
		{
			write(1, "freeing cmd	", ft_strlen("freeing cmd	"));
			free((tmp)->cmd);
		}
		if ((tmp)->tkn != NULL)
		{
			write(1, "freeing tkn	", ft_strlen("freeing tkn	"));
			free((tmp)->tkn);
		}
		if ((tmp)->env != NULL)
		{
			write(1, "freeing env	", ft_strlen("freeing env	"));
			free((tmp)->env);
		}
		free(tmp);
		tmp = next;
	}
	*grb = NULL;
}

// int	main(void)
// {
// 	char **split;
// 	char *hola;
// 	char **hello;
// 	char *halo;
// 	t_command *el_cmd;
// 	t_token *el_tkn;
// 	t_env *el_env;
// 	// int i;
// 	t_garbage *el_garbage;

// 	el_garbage = NULL;
// 	split = (char **)malloc(sizeof(char *) * 2);
// 	add_garbage(&el_garbage, new_garbage(split, D_CHAR));
// 	split[0] = strdup("yoyo");
// 	split[1] = strdup("heyhey");
// 	hello = (char **)malloc(sizeof(char *) * 2);
// 	add_garbage(&el_garbage, new_garbage(hello, D_CHAR));
// 	hello[0] = strdup("yoyo");
// 	hello[1] = strdup("heyhey");
// 	hola = strdup("cavamec");
// 	add_garbage(&el_garbage, new_garbage(hola, S_CHAR));
// 	halo = strdup("ouaiouai");
// 	add_garbage(&el_garbage, new_garbage(halo, S_CHAR));
// 	el_cmd = (t_command *)malloc(sizeof(t_command));
// 	add_garbage(&el_garbage, new_garbage(el_cmd, CMD));
// 	el_tkn = (t_token *)malloc(sizeof(t_token));
// 	add_garbage(&el_garbage, new_garbage(el_tkn, TKN));
// 	el_env = (t_env *)malloc(sizeof(t_env));
// 	add_garbage(&el_garbage, new_garbage(el_env, ENV));

// 	(void)halo;
// 	(void)hola;
// 	(void)el_cmd;
// 	(void)el_tkn;
// 	(void)el_env;

// 	clean_garbage(&el_garbage);

// 	// i = -1;
// 	// while (split[++i] != NULL)
// 	// {
// 	// 	free(split[i]);
// 	// }
// 	// free(split);
// 	// i = -1;
// 	// while (hello[++i] != NULL)
// 	// {
// 	// 	free(hello[i]);
// 	// }
// 	// free(hello);
// 	// free(hola);
// 	// free(halo);
// 	return (0);
// }