/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:06:53 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/02 19:38:51 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

char	*find_content_cd(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(name, tmp->name) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

int	change_dir(char *str, t_env *env, t_garbage **garbage)
{
	char	*buf;
	int		ret;

	if (!ft_strncmp(str, "~", 1))
		buf = ft_strdup(find_content_cd("HOME", env), garbage);
	else if (ft_strncmp(str, "-", 1) == 0)
		buf = ft_strdup(find_content_cd("OLDPWD", env), garbage);
	else
		buf = ft_strdup(str, garbage);
	if (!buf)
		exit(1);
	ret = chdir(buf);
	return (ret);
}

bool	is_single_cd(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] && is_whitespace(str[i]))
		++i;
	if (str[i] && str[i] == 'c')
		++i;
	if (str[i] && str[i] == 'd')
		++i;
	while (str[i] && is_whitespace(str[i]))
		++i;
	if (str[i] && str[i] == '~' && (!str[i + 1] || str[i + 1] == ' '))
		return (0);
	if (i != (int)ft_strlen(str))
		return (0);
	return (1);
}

void	exec_cd(t_command *cmd)
{
	char	pwd[500];

	if (cmd->arg->argz[1] == NULL)
		cmd->arg->argz[1] = ft_strdup("~", cmd->garbage);
	if (change_dir(cmd->arg->argz[1], cmd->env, cmd->garbage) == -1)
	{
		if (access(cmd->arg->argz[1], F_OK) == 0)
		{
			writing("groshell: cd: ", cmd->arg->argz[1]);
			write(1, ": Not a directory\n", ft_strlen(": Not a directory\n"));
			singleton(1, 1);
		}
		else
			ft_error("groshell: cd: ", cmd->arg->argz[1], 1, cmd->garbage);
		return ;
	}
	else
	{
		getcwd(pwd, 500);
		cmd->arg->argz[1] = ft_strjoin("OLDPWD="\
			, find_content_cd("PWD", cmd->env), cmd->garbage);
		exec_export(cmd);
		cmd->arg->argz[1] = ft_strjoin("PWD=", pwd, cmd->garbage);
		exec_export(cmd);
	}
}
