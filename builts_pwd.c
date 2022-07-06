#include "execution.h"

char *find_pwd(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void	exec_pwd(t_env *env)
{
	char *path;
	path = find_pwd(env);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
}