/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:28:28 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/03 13:40:18 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_parsed(t_command *cmd)
{
	t_token		*tmp;
	int			i;

	tmp = cmd->arg;
	if (cmd->arg != NULL)
	{
		if (tmp->content != NULL)
			writing("the content is:", tmp->content);
		if (tmp->command != NULL)
			writing("the command is:", tmp->command);
		if (tmp->path != NULL)
			writing("the path is:", tmp->path);
		i = -1;
		while (tmp->argz[++i])
			writing("the argz is : ", tmp->argz[i]);
	}
}

void	token_initing(t_token *arg, char **envp)
{
	arg->envp = envp;
	arg->unix_paths = NULL;
	arg->argz = NULL;
	arg->command = NULL;
	arg->path = NULL;
}

char	*ft_strjoin_new(char *s1, char *s2, int flag)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (str == NULL)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i++] = s2[j];
	str[i] = '\0';
	if (flag == 1 || flag == 2)
		free(s1);
	if (flag == 2)
		free(s2);
	return (str);
}
