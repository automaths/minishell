/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:07:09 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/02 14:41:18 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

int	check_export(char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (check_equal(str) == 0)
		return (0);
	while (str[i] && is_whitespace(str[i]))
		i++;
	while (str[i] && is_export(str[i]))
		i++;
	j = 0;
	while (str[i + j] && str[i + j] != '=')
		j++;
	if (j == 0)
		return (0);
	j++;
	k = 0;
	while (str[i + j + k])
		k++;
	if (k == 0)
		return (0);
	return (1);
}

char	*export_name(char *str, t_garbage **garbage)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	while (str[i] && is_whitespace(str[i]))
		i++;
	while (str[i] && is_export(str[i]))
		i++;
	while (str[i] && is_whitespace(str[i]))
		i++;
	j = 0;
	while (str[i + j] && str[i + j] != '=')
		j++;
	name = (char *)malloc(sizeof(char) * (j + 1));
	if (name == NULL)
		return (exiting_malloc(garbage), NULL);
	name[j] = '\0';
	j = -1;
	while (str[i + ++j] && str[i + j] != '=')
		name[j] = str[i + j];
	return (name);
}

char	*export_content(char *str, t_garbage **garbage)
{
	char	*content;
	int		i;
	int		j;

	i = 0;
	while (str[i] && is_whitespace(str[i]))
		i++;
	while (str[i] && is_export(str[i]))
		i++;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	j = 0;
	while (str[i + j])
		j++;
	content = (char *)malloc(sizeof(char) * (j + 1));
	if (content == NULL)
		return (exiting_malloc(garbage), NULL);
	add_garbage(garbage, new_garbage(content, S_CHAR));
	content[j] = '\0';
	j = -1;
	while (str[i + ++j])
		content[j] = str[i + j];
	return (content);
}

int	update_env(char *name, char *content, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(name, tmp->name) == 0)
		{
			tmp->name = name;
			tmp->content = content;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	exec_export(t_command *cmd)
{
	char	*name;
	char	*content;

	if (cmd->arg->argz[1] == NULL)
	{
		print_export(cmd);
		return ;
	}
	if (check_export(cmd->arg->argz[1]) == 0)
	{
		write(1, "export: not a valid identifier\n", ft_strlen("export: not a valid identifier\n"));
		singleton(1, 1);
		return ;
	}
	name = export_name(cmd->arg->argz[1], cmd->garbage);
	content = export_content(cmd->arg->argz[1], cmd->garbage);
	if (update_env(name, content, cmd->env))
	{
		update_all_envz(cmd, cmd->env);
		return ;
	}
	add_back_env(name, content, cmd->env);
	update_all_envz(cmd, cmd->env);
}
