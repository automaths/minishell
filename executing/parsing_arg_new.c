/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:33:05 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/02 19:45:34 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../groshell.h"

bool	get_the_path_one(t_command *cmd)
{
	int		i;
	char	**envp;

	i = 0;
	envp = envp_to_char(cmd->env);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (0);
	cmd->arg->unix_paths = ft_split(&envp[i][4], ':', cmd->garbage);
	if (cmd->arg->command == NULL)
		return (0);
	return (1);
}

bool	get_the_path(t_command *cmd)
{
	int		i;

	if (command_trim(cmd) == 0)
		return (ft_error(cmd->arg->command, (char *) NULL, 127, 1), 0);
	if (is_builts(cmd->arg->command))
		return (1);
	if (check_local_exec(cmd->arg->command))
		return (1);
	if (check_absolute(cmd))
		return (1);
	if (get_the_path_one(cmd) == 0)
		return (ft_error(cmd->arg->command, (char *) NULL, 127, 1), 0);
	i = 0;
	while (cmd->arg->unix_paths[i] \
		&& find_path(cmd->arg, cmd->arg->unix_paths[i]) == 0)
		i++;
	if (cmd->arg->unix_paths[i] == NULL)
		return (ft_error(cmd->arg->command, (char *) NULL, 127, 1), 0);
	if (cmd->arg->path == NULL)
		return (ft_error(cmd->arg->command, (char *) NULL, 127, 1), 0);
	return (1);
}

int	count_token(t_token *tkn)
{
	t_token	*tmp_tkn;
	int		i;

	tmp_tkn = tkn;
	i = 0;
	while (tmp_tkn != NULL)
	{
		i++;
		tmp_tkn = tmp_tkn->next;
	}
	return (i);
}

bool	parse_argument_one(t_command *cmd)
{
	if (cmd->arg == NULL)
		return (0);
	token_initing(cmd);
	if (get_the_path(cmd) == 0)
		return (0);
	return (1);
}

bool	parse_argument(t_command *cmd)
{
	t_token	*tmp_tkn;
	int		i;
	int		j;

	if (parse_argument_one(cmd) == 0)
		return (0);
	i = count_token(cmd->arg);
	if (i == 0)
		return (0);
	cmd->arg->argz = (char **)malloc(sizeof(char *) * (i + 2));
	if (cmd->arg->argz == NULL)
		return (exiting_malloc(cmd->garbage), NULL);
	add_garbage(cmd->garbage, new_garbage(cmd->arg->argz, D_CHAR));
	tmp_tkn = cmd->arg;
	cmd->arg->argz[0] = cmd->arg->command;
	tmp_tkn = tmp_tkn->next;
	j = 0;
	while (++j < i)
	{
		cmd->arg->argz[j] = tmp_tkn->content;
		tmp_tkn = tmp_tkn->next;
	}
	cmd->arg->argz[j] = NULL;
	return (1);
}
