#include "../execution.h"

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

