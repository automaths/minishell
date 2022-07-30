/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 21:02:45 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/31 00:25:02 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

void	negativ_quote(char *str)
{
	int	i;
	int	quote;

	i = 0;
	while (str[i])
	{
		quote = what_state(str, i);
		if ((str[i] == '\"' && quote == 1) || (str[i] == '\'' && quote == 2))
			str[i] *= -1;
		i++;
	}
}

char	*del_one_neg_quotes(char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((str[i] == '\"') || (str[i] == '\''))
			j++;
	}
	dest = malloc(sizeof(char) * ((i - j) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
			dest[j++] = str[i++];
		else
			i++;
	}
	dest[i] = 0;
	return (dest);
}

int	del_all_neg_quotes(t_command *cmd)
{
	t_token		*tmp;

	tmp = cmd->arg;
	while (tmp)
	{
		tmp->content = del_one_neg_quotes(tmp->content);
		if (!tmp->content)
			return (0);
		tmp = tmp->next;
	}
	replace_negativ_char_redir(cmd);
	return (1);
}

int	del_quotes(t_command *cmd)
{
	t_token		*tmp;

	tmp = cmd->arg;
	while (tmp)
	{
		negativ_quote(tmp->content);
		tmp = tmp->next;
	}
	if (!del_all_neg_quotes(cmd))
		return (0);
	return (1);
}
