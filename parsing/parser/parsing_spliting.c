/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_spliting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:47:07 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 11:38:26 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"


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
