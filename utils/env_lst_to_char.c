/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:39:13 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 21:35:35 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../groshell.h"

int	lst_len(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		++i;
	}
	return (i);
}

char	*alloc_line(char *name, char *content, t_garbage **garbage)
{
	char	*line;
	int		i;
	int		j;

	line = (char *)malloc(sizeof(char) * (ft_strlen(name) \
		+ ft_strlen(content) + 2));
	if (line == NULL)
		return (exiting_malloc(garbage), NULL);
	add_garbage(garbage, new_garbage(line, S_CHAR));
	i = -1;
	while (name[++i])
		line[i] = name[i];
	line[i++] = '=';
	j = -1;
	while (content[++j])
		line[i + j] = content[j];
	line[i + j] = '\0';
	return (line);
}

char	**envp_to_char(t_env *env)
{
	char	**split;
	t_env	*tmp;
	int		i;

	tmp = env;
	split = (char **)malloc(sizeof(char *) * (lst_len(env) + 1));
	if (split == NULL)
		return (exiting_malloc(env->garbage), NULL);
	add_garbage(env->garbage, new_garbage(split, D_CHAR));
	split[lst_len(env)] = NULL;
	i = -1;
	while (tmp != NULL)
	{
		split[++i] = alloc_line(tmp->name, tmp->content, env->garbage);
		tmp = tmp->next;
	}
	return (split);
}
