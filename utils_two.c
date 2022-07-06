/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:39:36 by nimrod            #+#    #+#             */
/*   Updated: 2022/07/06 21:17:37 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	is_whitespace(char c)
{
	if (c == ' ' && c == '\t' && c == '\v'
		&& c == '\n' && c == '\r' && c == '\f')
		return (1);
	return (0);
}

bool	is_whitespace2(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\n' || c == '\r' || c == '\f')
		return (1);
	return (0);
}

bool	is_lowercase(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

bool	is_printable_except_space(char c)
{
	if (c < 33 || c > 126)
		return (0);
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	i = 0;
	while (one[i] && two[i] && one[i] == two[i])
		i++;
	return (one[i] - two[i]);
}

int	lst_len(t_env *env)
{
	t_env *tmp;
	int i;
	
	tmp = env;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		++i;
	}
	return (i);
}

char	*alloc_line(char *name, char *content)
{
	char *line;
	int i;
	int j;
	
	line = (char *)malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(content) + 2));
	if (line == NULL)
		return (NULL);
	i = -1;
	while (name[++i])
		line[i] = name[i];
	line[i++] = '=';
	j = -1;
	while (content[++j])
		line[i + j] = content[j];
	return (line);
}

char **envp_to_char(t_env *env)
{
	char **split;
	t_env *tmp;
	int i;
	
	tmp = env;
	split = (char **)malloc(sizeof(char *) * (lst_len(env) + 1));
	if (split == NULL)
		return (NULL);
	split[lst_len(env)] = NULL;
	i = -1;
	while (tmp != NULL)
	{
		split[++i] = alloc_line(tmp->name, tmp->content);
		tmp = tmp->next;
	}
	return (split);
}
