/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:06:53 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/07 19:05:25 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// char	*find_content_cd(char *name, t_list *env)
// {
// 	t_list *tmp;
	
// 	tmp = env;
// 	while (tmp != NULL)
// 	{
// 		if (ft_strcmp(name, tmp->name) == 0)
// 			return (tmp->content);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// int	change_dir(char *str, t_list *env)
// {
// 	char	*buf;
// 	int		ret;

// 	if (!ft_strncmp(str, "~", 1))
// 		buf = ft_strdup(find_content("HOME", env));
// 	else if (ft_strncmp(str, "-", 1) == 0)
// 		buf = ft_strdup(find_content("OLDPWD", env));
// 	else
// 		buf = ft_strdup(str);
// 	if (!buf)
// 		exit(1);
// 	ret = chdir(buf);
// 	free(buf);
// 	return (ret);
// }

// bool	is_single_cd(char *str)
// {
// 	int i;
	
// 	i = 0;
// 	while (str[i] && is_whitespace2(str[i]))
// 		++i;
// 	if (str[i] && str[i] == 'c')
// 		++i;
// 	if (str[i] && str[i] == 'd')
// 		++i;
// 	while (str[i] && is_whitespace2(str[i]))
// 		++i;
// 	if (i != ft_strlen(str))
// 		return (0);
// 	return (1);
	
// }

// void	exec_cd(char *str, t_list *env)
// {
// 	char	pwd[500];
// 	char	*update;

// 	if (is_single_cd(str))
// 		change_dir("~", env);
// 	if (change_dir(str, env) == -1)
// 	{
// 		write(1, "bash: cd: ", ft_strlen("bash: cd: "));
// 		write(1, str, ft_strlen(str));
// 		write(1, ": No such file or directory\n", 29);
// 		return ;
// 	}
// 	else
// 	{
// 		getcwd(pwd, 500);
// 		update = ft_strjoin("OLDPWD=", find_content_cd("PWD", env));
// 		exec_export(update, env);
// 		free(update);
// 		update = ft_strjoin("PWD=", pwd);
// 		exec_export(update, env);
// 		free(update);
// 	}
// }

void	exec_cd(t_command *cmd)
{
	(void)cmd;
}
