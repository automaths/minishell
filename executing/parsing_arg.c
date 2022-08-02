/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:16 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/02 13:54:28 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../groshell.h"

void	token_initing(t_command *cmd)
{
	cmd->arg->unix_paths = NULL;
	cmd->arg->argz = NULL;
	cmd->arg->command = NULL;
	cmd->arg->path = NULL;
}

bool	command_trim(t_command *cmd)
{
	int		j;

	j = 0;
	while (is_printable_except_space(cmd->arg->content[j]))
		j++;
	if (j == 0)
		return (0);
	cmd->arg->command = (char *)malloc(sizeof(char) * (j + 1));
	if (cmd->arg->command == NULL)
		return (NULL);
	add_garbage(cmd->garbage, new_garbage(cmd->arg->command, S_CHAR));
	j = 0;
	while (is_printable_except_space(cmd->arg->content[j]))
	{
		cmd->arg->command[j] = cmd->arg->content[j];
		j++;
	}
	cmd->arg->command[j] = '\0';
	return (1);
}

bool	find_path(t_token *arg, char *unix_path)
{
	char	slash[2];

	slash[0] = '/';
	slash[1] = '\0';
	arg->path = ft_strjoin_new(unix_path, slash, arg->garbage);
	if (arg->path == NULL)
		return (0);
	arg->path = ft_strjoin_new(arg->path, arg->command, arg->garbage);
	if (arg->path == NULL)
		return (0);
	if (access(arg->path, X_OK) == 0)
		return (1);
	return (0);
}

bool	is_builts(char *command)
{
	if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}

bool	check_absolute(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->arg->command[++i])
	{
		if (cmd->arg->command[i] == '/')
		{
			if (access(cmd->arg->command, X_OK) == 0)
			{
				cmd->arg->path = cmd->arg->command;
				return (1);
			}
			else
				return (0);
		}
	}
	return (0);
}
