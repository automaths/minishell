/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_spliting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:47:07 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/29 17:36:17 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

char	**spliting_plus(char *str)
{
	char	*str_quoted;
	char	**split;

	str_quoted = quoting_ruling(str);
	split = ft_split(str_quoted, ' ');
	if (split == NULL)
		return (NULL);
	split = split_cleaning(split);
	return (split);
}

char	*quoting_ruling(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			str[i] = ' ';
			while (str[++i] && str[i] != '"')
			{
				if (str[i] == ' ')
					str[i] = '*';
			}
			str[i] = ' ';
		}
	}
	return (str);
}

char	**split_cleaning(char **split)
{
	int	i;
	int	j;

	i = -1;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
		{
			if (split[i][j] == '*')
				split[i][j] = ' ';
		}
	}
	return (split);
}
