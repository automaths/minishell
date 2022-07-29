/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:06:53 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/29 14:40:17 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

char	*find_content_cd(char *name, t_env *env)
{
	t_env *tmp;
	
	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(name, tmp->name) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

int	change_dir(char *str, t_env *env)
{
	char	*buf;
	int		ret;

	if (!ft_strncmp(str, "~", 1))
		buf = ft_strdup(find_content_cd("HOME", env));
	else if (ft_strncmp(str, "-", 1) == 0)
		buf = ft_strdup(find_content_cd("OLDPWD", env));
	else
		buf = ft_strdup(str);
	if (!buf)
		exit(1);
	ret = chdir(buf);
	free(buf);
	return (ret);
}

bool	is_single_cd(char *str)
{
	int i;
	
	i = 0;
	while (str[i] && is_whitespace2(str[i]))
		++i;
	if (str[i] && str[i] == 'c')
		++i;
	if (str[i] && str[i] == 'd')
		++i;
	while (str[i] && is_whitespace2(str[i]))
		++i;
	if (i != (int)ft_strlen(str))
		return (0);
	return (1);
	
}

void	exec_cd(t_command *cmd)
{
	char	pwd[500];

	if (is_single_cd(cmd->arg->argz[1]))
		change_dir("~", cmd->env);
	if (change_dir(cmd->arg->argz[1], cmd->env) == -1)
	{
		write(1, "bash: cd: ", ft_strlen("bash: cd: "));
		write(1, cmd->arg->argz[1], ft_strlen(cmd->arg->argz[1]));
		write(1, ": No such file or directory\n", 29);
		return ;
	}
	else
	{
		getcwd(pwd, 500);
		cmd->arg->argz[1] = ft_strjoin("OLDPWD=", find_content_cd("PWD", cmd->env));
		exec_export(cmd);
		free(cmd->arg->argz[1]);
		cmd->arg->argz[1] = ft_strjoin("PWD=", pwd);
		exec_export(cmd);
		free(cmd->arg->argz[1]);
	}
}
