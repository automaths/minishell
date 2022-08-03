/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 21:49:48 by jucheval          #+#    #+#             */
/*   Updated: 2022/08/03 15:34:18 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../groshell.h"

char	*find_variable_value(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, &name[0]) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*string_with_var_value(char *cmd, char *name, int size_old_var, \
	t_command *t_cmd)
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
	if (name)
		while (name[k])
			dest[j++] = name[k++];
	i++;
	while (cmd[i] && cmd[i] != '$' && ft_isalnum(cmd[i]))
		i++;
	while (cmd[i])
		dest[j++] = cmd[i++];
	dest[j] = 0;
	return (dest);
}

char	*replace_one_variable(char *str, t_env *env, int i, t_command *cmd)
{
	int		j;
	char	*variable_name;

	j = 0;
	while (str[i] && str[i] != '$' && ft_isalnum(str[i]))
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
	while (str[i] && str[i] != '$' && ft_isalnum(str[i]))
		variable_name[j++] = str[i++];
	variable_name[j] = 0;
	variable_name = find_variable_value(variable_name, env);
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
					tmp_token->content = replace_one_variable(tmp_token->content, env, ++i, cmd);
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
	t_command	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		parse_dollars(tmp);
		parse_dollars_redir(tmp);
		replace_return_value(tmp);
		if (!replace_variable(tmp, env))
			return (0);
		if (!replace_variable_redir(tmp, env))
			return (0);
		replace_negativ_char(tmp);
		replace_negativ_char_redir(tmp);
		if (!del_quotes(tmp))
			return (0);
		if (!delete_redir_char_in_redir_list(tmp))
			return (0);
		if (!delete_quotes_redir_list(tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
