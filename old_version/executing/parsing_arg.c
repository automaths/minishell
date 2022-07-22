/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:16 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/08 08:33:13 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	token_initing(t_command *cmd)
{
	cmd->arg->unix_paths = NULL;
	cmd->arg->argz = NULL;
	cmd->arg->command = NULL;
	cmd->arg->path = NULL;
}

bool	command_trim(t_command *cmd)
{
	int		i;
	int		j;

	i = 0;
	while (is_whitespace(cmd->arg->content[i]))
		i++;
	j = 0;
	while (is_printable_except_space(cmd->arg->content[i + j]))
		j++;
	if (j == 0)
		return (0);
	cmd->arg->command = (char *)malloc(sizeof(char) * (j + 1));
	if (cmd->arg->command == NULL)
		return (0);
	j = 0;
	while (is_printable_except_space(cmd->arg->content[i + j]))
	{
		cmd->arg->command[j] = cmd->arg->content[i + j];
		j++;
	}
	cmd->arg->command[j] = '\0';
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

bool	get_the_path(t_command *cmd)
{
	int	i;
	char **envp;

	i = 0;
	envp = envp_to_char(cmd->env);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (0);
	cmd->arg->unix_paths = ft_split(&envp[i][4], ':');
	if (cmd->arg->unix_paths == NULL)
		return (0);
	if (command_trim(cmd) == 0)
		return (freeing_unix(cmd->arg), writing_error(NULL, CMD_NOT_FOUND), 0);
	if (cmd->arg->command == NULL)
		return (0);
	if (is_builts(cmd->arg->command))
		return (1);
	i = 0;
	while (cmd->arg->unix_paths[i] && find_path(cmd->arg, cmd->arg->unix_paths[i]) == 0)
		i++;
	if (cmd->arg->unix_paths[i] == NULL)
		return (writing_error(cmd->arg->command, CMD_NOT_FOUND)
			, freeing_unix(cmd->arg), free(cmd->arg->command), 0);
	if (cmd->arg->path == NULL)
		return (writing_error(cmd->arg->command, CMD_NOT_FOUND)
			, freeing_unix(cmd->arg), free(cmd->arg->command), 0);
	return (freeing_unix(cmd->arg), 1);
}

// bool	parse_argument(t_command *cmd)
// {
// 	char	**tmp;
// 	int		i;
// 	int		j;

// 	token_initing(cmd);
// 	if (get_the_path(cmd) == 0)
// 		return (0);
// 	i = 0;
// 	tmp = ft_split(cmd->arg->content, ' ');
// 	while (tmp[i])
// 		i++;
// 	if (i == 0)
// 		return (0);
// 	cmd->arg->argz = (char **)malloc(sizeof(char *) * (i + 2));
// 	if (cmd->arg->argz == NULL)
// 		return (0);
// 	cmd->arg->argz[0] = cmd->arg->command;
// 	j = 0;
// 	while (++j <= i)
// 		cmd->arg->argz[j] = tmp[j];
// 	cmd->arg->argz[j] = NULL;
// 	free(tmp[0]);
// 	free(tmp);
// 	return (1);
// }
