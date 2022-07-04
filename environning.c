#include "execution.h"

bool	check_envz(char *str)
{
	int i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (!is_whitespace(str[i + 1]))
				return (1);
		}
	}
	return (0);
}

char	*updated_env(char *str, char *name, char *content)
{
	char *new;
	int i;
	int j;

	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(content) - ft_strlen(name) + 1));
	if (new == NULL)
		return (NULL);
	new[ft_strlen(str) + ft_strlen(content) - ft_strlen(name)] = '\0';
	i = -1;
	while (++i < strnstr_int(str, name))
		new[i] = str[i];
	j = -1;
	while (++j < (int)ft_strlen(content))
		new[i + j] = content[j];
	--i;
	while (str[++i + ft_strlen(name)])
		new[i + j] = str[i + ft_strlen(name)];
	return (new);
}

char	*find_content(char *name, t_env *env)
{
	t_env *tmp;

	printf("%s", name);
	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, &name[1], (ft_strlen(name) - 1)) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*change_envz(char *str, t_env *env)
{
	int i;
	int j;
	char *name;
	char *content;
	
	i = -1;
	while (str[++i] && (str[i] != '$' || is_whitespace(str[i + 1])))
		;
	j = -1;
	while (str[i + ++j] && !is_whitespace(str[i + j]) && str[i + j] != ' ')
		;
	name = (char *)malloc(sizeof(char) * (j + 1));
	if (name == NULL)
		return (NULL);
	name[j] = '\0';
	j = -1;
	while (str[i + ++j] && !is_whitespace(str[i + j]) && str[i + j] != ' ')
		name[j] = str[i + j];
	content = find_content(name, env);
	printf("the str is : %s\n the name is %s\n the content is %s\n", str, name, content);
	str = updated_env(str, name, content);
	return (str);
}

char	*environning(char *str, t_env *env)
{
	while (check_envz(str))
		str = change_envz(str, env);
	return (str);
}
