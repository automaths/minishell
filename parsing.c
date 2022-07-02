/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:16 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/02 14:53:12 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	command_trim(t_token *arg)
{
	int		i;
	int		j;

	i = 0;
	while (is_whitespace(arg->content[i]))
		i++;
	j = 0;
	while (is_printable_except_space(arg->content[i + j]))
		j++;
	if (j == 0)
		return (0);
	arg->command = (char *)malloc(sizeof(char) * (j + 1));
	if (arg->command == NULL)
		return (0);
	j = 0;
	while (is_printable_except_space(arg->content[i + j]))
	{
		arg->command[j] = arg->content[i + j];
		j++;
	}
	arg->command[j] = '\0';
	// write(1, "the command trimmed is :", ft_strlen("the command trimmed is :"));
	// write(1, arg->command, ft_strlen(arg->command));
	// return (0);
	return (1);
}

bool	find_path(t_token *arg, char *unix_path)
{
	char	slash[1];

	slash[0] = '/';
	arg->path = ft_strjoin_new(unix_path, slash, 0);
	if (arg->path == NULL)
		return (0);
	arg->path = ft_strjoin_new(arg->path, arg->command, 1);
	if (arg->path == NULL)
		return (0);
	if (access(arg->path, X_OK) == 0)
		return (1);
	return (free(arg->path), 0);
}

bool	get_the_path(t_token *arg)
{
	int	i;

	i = 0;
	while (arg->envp[i] && ft_strncmp(arg->envp[i], "PATH=", 5) != 0)
		i++;
	if (arg->envp[i] == NULL)
		return (0);
	arg->unix_paths = ft_split(&arg->envp[i][4], ':');
	if (arg->unix_paths == NULL)
		return (0);
	if (command_trim(arg) == 0)
		return (freeing_unix(arg), writing_error(NULL, CMD_NOT_FOUND), 0);
	if (arg->command == NULL)
		return (0);
	i = 0;
	while (arg->unix_paths[i] && find_path(arg, arg->unix_paths[i]) == 0)
		i++;
	if (arg->unix_paths[i] == NULL)
		return (writing_error(arg->command, CMD_NOT_FOUND), freeing_unix(arg), free(arg->command), 0);
	if (arg->path == NULL)
		return (writing_error(arg->command, CMD_NOT_FOUND), freeing_unix(arg), free(arg->command), 0);
	// write(1, "the path is :", ft_strlen("the path is"));
	// write(1, arg->path, ft_strlen(arg->path));
	// return (0);
	return (freeing_unix(arg), 1);
}

bool	parse_argument(t_token *arg, char **envp)
{
	char	**tmp;
	int		i;
	int		j;

	token_initing(arg, envp);
	if (get_the_path(arg) == 0)
		return (0);
	i = 0;
	tmp = ft_split(arg->content, ' ');
	while (tmp[i])
		i++;
	if (i == 0)
		return (0);
	arg->argz = (char **)malloc(sizeof(char *) * (i + 2));
	if (arg->argz == NULL)
		return (0);
	arg->argz[0] = arg->command;
	j = 0;
	while (++j <= i)
		arg->argz[j] = tmp[j];
	arg->argz[j] = NULL;
	free(tmp[0]);
	free(tmp);
	return (1);
}
