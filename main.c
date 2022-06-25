#include "execution.h"

char	*ft_strjoin_new(char *s1, char *s2, int flag)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen_bis(s1) + ft_strlen_bis(s2)) + 1);
	if (str == NULL)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i++] = s2[j];
	str[i] = '\0';
	if (flag == 1 || flag == 2)
		free(s1);
	if (flag == 2)
		free(s2);
	return (str);
}

// A RETAPER
char	*command_trim(char *str)
{
	char *command;
	int		i;
	int		j;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	j = 0;
	while (is_lowercase(str[i + j]))
		j++;
	if (j == 0)
		return (0);
	command = (char *)malloc(sizeof(char) * (j + 1));
	if (command == NULL)
		return (0);
	j = 0;
	while (is_lowercase(str[i + j]))
	{
		command[j] = str[i + j];
		j++;
	}
	command[j] = '\0';
	return (command);
}

bool	find_path(t_struct *dd, char *unix_path)
{
	char	add[1];

	add[0] = '/';
	dd->path = ft_strjoin_new(unix_path, add, 0);
	if (dd->path == NULL)
		return (0);
	dd->path = ft_strjoin_new(dd->path, dd->command, 1);
	if (dd->path == NULL)
		return (0);
	if (access(dd->path, X_OK) == 0)
		return (1);
	return (free(dd->path), 0);
}

bool	get_the_path(t_struct *dd)
{
	if (command_trim(dd) == 0)
		return (freeing_unix(dd), 0);
	if (dd->command == NULL)
		return (0);
	i = 0;
	while (dd->unix_paths[i] && find_path(dd, dd->unix_paths[i]) == 0)
		i++;
	if (dd->unix_paths[i] == NULL)
		return (freeing_unix(dd), free(dd->command), 0);
	return (freeing_unix(dd), 1);
}

char	**get_unix_paths(char **envp)
{
	char **unix_paths;
	char *command;
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	unix_paths = ft_split(&envp[i][4], ':');
	if (unix_paths == NULL)
		return (NULL);
	command = command_trim();
}

bool	parse_arguments(char **split, char **envp)
{
	char **unix_paths;
	char *commmand;

	unix_paths = get_unix_paths(envp);
	if (unix_paths == NULL)
		return (printf("environnement error"), 0);
	



	//COMMAND TRIM
	
	
	// int		i;
	// int		j;
	// if (dd->path == NULL)
	// 	return (0);
	// i = 0;
	// tmp = ft_split(dd->argv[dd->c], ' ');
	// while (tmp[i])
	// 	i++;
	// if (i == 0)
	// 	return (0);
	// dd->argz = (char **)malloc(sizeof(char *) * (i + 2));
	// if (dd->argz == NULL)
	// 	return (0);
	// dd->argz[0] = dd->command;
	// j = 0;
	// while (++j <= i)
	// 	dd->argz[j] = tmp[j];
	// dd->argz[j] = NULL;
	// free(tmp[0]);
	// free(tmp);
	return (1);
}
