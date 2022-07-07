/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:07:09 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/07 17:12:02 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool	is_export(char c)
{
	if (c == 'e' || c == 'x' || c == 'p' || c == 'o' || c == 'r' || c == 't')
		return (1);
	return (0);
}

bool	check_equal(char *str)
{
	int i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (1);
	}
	return (0);
}

int	check_export(char *str)
{
	int i;
	int j;
	int k;
	
	i = 0;
	if (check_equal(str) == 0)
		return (printf("no equal"), 0);
	while (str[i] && is_whitespace2(str[i]))
		i++;
	while (str[i] && is_export(str[i]))
		i++;
	j = 0;
	while (str[i + j] && str[i + j] != '=')
		j++;
	if (j == 0)
		return (printf("incorrect export format"), 0);
	j++;
	k = 0;
	while (str[i + j + k])
		k++;
	if (k == 0)
		return (printf("incorrect export format"), 0);
	return (1);
}

char	*export_name(char *str)
{
	char *name;
	int i;
	int j;
	
	i = 0;
	while (str[i] && is_whitespace2(str[i]))
		i++;
	while (str[i] && is_export(str[i]))
		i++;
	while (str[i] && is_whitespace2(str[i]))
		i++;
	j = 0;
	while (str[i + j] && str[i + j] != '=')
		j++;
	name = (char *)malloc(sizeof(char) * (j + 1));
	if (name == NULL)
		return (NULL);
	name[j] = '\0';
	j = -1;
	while (str[i + ++j] && str[i + j] != '=')
		name[j] = str[i + j];
	return (name);
}

char	*export_content(char *str)
{
	char *content;
	int i;
	int j;
	while (str[i] && is_whitespace2(str[i]))
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
		return (NULL);
	content[j] = '\0';
	j = -1;
	while (str[i + ++j])
		content[j] = str[i + j];
	return (content);
}

void	add_back_env(char *name, char *content, t_env *env)
{
	t_env *tmp;
	
	tmp = env;
	if (tmp == NULL)
		return ;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_lst(name, content);
}

int	update_env(char *name, char *content, t_env *env)
{
	t_env *tmp;

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

void	read_envz(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp != NULL)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, "=", 1);
		write(1, tmp->content, ft_strlen(tmp->content));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

void	update_all_envz(t_command *cmd, t_env *env)
{
	t_command *tmp;
	
	tmp = cmd;
	while (tmp != NULL)
	{
		tmp->env = env;
		tmp = tmp->next;
	}
}

void	exec_export(t_command *cmd)
{
	char *name;
	char *content;

	if (check_export(cmd->arg->argz[1]) == 0)
		return ;
	name = export_name(cmd->arg->argz[1]);
	content = export_content(cmd->arg->argz[1]);
	if(update_env(name, content, cmd->env))
		return ;
	add_back_env(name, content, cmd->env);
	// read_envz(cmd->env);
	update_all_envz(cmd, cmd->env);
}
