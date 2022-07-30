/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 21:04:46 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/30 21:05:07 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

char	*string_with_return_var_value(char *cmd, char *name, int size_old_var)
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
		return (NULL);
	while (cmd[i] && (cmd[i] != '$' && cmd[i + 1] != '?'))
		dest[j++] = cmd[i++];
	while (name[k])
		dest[j++] = name[k++];
	i += 2;
	while (cmd[i])
		dest[j++] = cmd[i++];
	return (dest);
}

char	*replace_one_return_value(char *str)
{
	char	*variable_name;

	variable_name = ft_itoa(singleton(0, 0));
	if (!variable_name)
		return (0);
	str = string_with_return_var_value(str, variable_name, 2);
	if (!str)
		return (NULL);
	return (str);
}

int	replace_return_value(t_command *cmd)
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
				if (tmp_token->content[i] == '$' && tmp_token->content[i + 1] == '?')
				{
					tmp_token->content = replace_one_return_value(tmp_token->content);
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