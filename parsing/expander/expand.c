/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 21:49:48 by jucheval          #+#    #+#             */
/*   Updated: 2022/08/01 18:25:44 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

char	*find_variable_value(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, &name[1], (ft_strlen(name) - 1)) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*string_with_var_value(char *cmd, char *name, int size_old_var, t_command *t_cmd)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	i = 0;
	j = 0;
	k = 0;
	dest = malloc(sizeof(char) * ((ft_strlen(cmd) - size_old_var) + \
	ft_strlen(name) + 1));
	if (!dest)
		return (exiting_malloc(t_cmd->garbage), NULL);
	add_garbage(t_cmd->garbage, new_garbage(dest, S_CHAR));
	while (cmd[i] && cmd[i] != '$')
		dest[j++] = cmd[i++];
	while (name[k])
		dest[j++] = name[k++];
	while (cmd[i] && ft_isalnum(cmd[i]))
		i++;
	while (cmd[i])
		dest[j++] = cmd[i++];
	return (dest);
}

char	*replace_one_variable(char *str, t_env *env, int i, t_command *cmd)
{
	int		j;
	char	*variable_name;

	j = 0;
	while (str[i] && ft_isalnum(str[i]))
	{
		i++;
		j++;
	}
	variable_name = malloc(sizeof(char) * (j + 1));
	if (!variable_name)
		return (exiting_malloc(cmd->garbage), NULL);
	add_garbage(cmd->garbage, new_garbage(variable_name, S_CHAR));
	i -= j;
	j = 0;
	while (str[i] && ft_isalnum(str[i]))
		variable_name[j++] = str[i++];
	variable_name[j] = 0;
	variable_name = find_variable_value(variable_name, env);
	if (!variable_name)
		return (0);
	str = string_with_var_value(str, variable_name, j, cmd);
	if (!str)
		return (NULL);
	return (str);
}

int	replace_variable(t_command *cmd, t_env *env)
{
	int			i;
	t_command	*tmp;
	t_token		*tmp_token;

	tmp = cmd;
	while (tmp)
	{
		tmp_token = tmp->arg;
		while (tmp_token)
		{
			i = -1;
			while (tmp_token->content[++i])
			{
				if (tmp_token->content[i] == '$')
				{
					tmp_token->content = \
					replace_one_variable(tmp_token->content, env, i, cmd);
					if (!tmp_token->content)
						return (0);
				}
			}
			tmp_token = tmp_token->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	replace_all_variable(t_command *cmd, t_env *env)
{
	parse_dollars(cmd);
	parse_dollars_redir(cmd);
	replace_return_value(cmd);
	if (!replace_variable(cmd, env))
		return (0);
	if (!replace_variable_redir(cmd, env))
		return (0);
	replace_negativ_char(cmd);
	replace_negativ_char_redir(cmd);
	if (!del_quotes(cmd))
		return (0);
	if (!delete_redir_char_in_redir_list(cmd))
		return (0);
	if (!delete_quotes_redir_list(cmd))
		return (0);
	return (1);
}
