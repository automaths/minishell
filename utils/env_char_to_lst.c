/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_char_to_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:55:44 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/29 17:55:51 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*get_content(char *envp)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (envp[++i] && envp[i] != '=')
		;
	++i;
	while (envp[i + ++j])
		;
	str = (char *)malloc(sizeof(char) * (j + 1));
	if (str == NULL)
		return (NULL);
	str[j] = '\0';
	j = -1;
	while (envp[i + ++j])
		str[j] = envp[i + j];
	return (str);
}

char	*get_name(char *envp)
{
	char	*str;
	int		i;

	i = -1;
	while (envp[++i] && envp[i] != '=')
		;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	i = -1;
	while (envp[++i] && envp[i] != '=')
		str[i] = envp[i];
	return (str);
}

t_env	*env_to_list(char **envp)
{
	int		i;
	t_env	*env;

	env = NULL;
	if (envp[0] == NULL)
		return (printf("no env"), NULL);
	if (check_envp(envp) == 0)
		return (NULL);
	i = -1;
	while (envp[++i])
		add_back_lst(&env, new_lst(get_name(envp[i]), get_content(envp[i])));
	return (env);
}
