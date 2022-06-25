#include "execution.h"

void	print_parsed(t_command *cmd)
{
	if (cmd->arg != NULL)
	{
		if (cmd->arg->content != NULL)
			writing("the content is:", cmd->arg->content);
		if (cmd->arg->command != NULL)
			writing("the command is:", cmd->arg->command);
		if (cmd->arg->path != NULL)
			writing("the path is:", cmd->arg->path);
	}
}

void	token_initing(t_token *arg, char **envp)
{
	arg->envp = envp;
	arg->command = NULL;
	arg->argz = NULL;
	arg->path = NULL;
	arg->command = NULL;
	arg->unix_paths = NULL;
}

char	*ft_strjoin_new(char *s1, char *s2, int flag)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
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

bool	command_trim(t_token *arg)
{
	int		i;
	int		j;

	i = 0;
	while (is_whitespace(arg->content[i]))
		i++;
	j = 0;
	while (is_lowercase(arg->content[i + j]))
		j++;
	if (j == 0)
		return (0);
	arg->command = (char *)malloc(sizeof(char) * (j + 1));
	if (arg->command == NULL)
		return (0);
	j = 0;
	while (is_lowercase(arg->content[i + j]))
	{
		arg->command[j] = arg->content[i + j];
		j++;
	}
	arg->command[j] = '\0';
	return (1);
}

bool	find_path(t_token *arg, char *unix_path)
{
	char	aarg[1];

	aarg[0] = '/';
	arg->path = ft_strjoin_new(unix_path, aarg, 0);
	if (arg->path == NULL)
		return (0);
	arg->path = ft_strjoin_new(arg->path, arg->command, 1);
	if (arg->path == NULL)
		return (0);
	if (access(arg->path, X_OK) == 0)
		return (1);
	return (free(arg->path), 0);
}

bool	get_the_path(t_token *arg)
{
	int	i;

	i = 0;
	while (arg->envp[i] && ft_strncmp(arg->envp[i], "PATH=", 5) != 0)
		i++;
	if (arg->envp[i] == NULL)
		return (0);
	arg->unix_paths = ft_split(&arg->envp[i][4], ':');
	if (arg->unix_paths == NULL)
		return (0);
	if (command_trim(arg) == 0)
		return (freeing_unix(arg), 0);
	if (arg->command == NULL)
		return (0);
	i = 0;
	while (arg->unix_paths[i] && find_path(arg, arg->unix_paths[i]) == 0)
		i++;
	if (arg->unix_paths[i] == NULL)
		return (freeing_unix(arg), free(arg->command), 0);
	return (freeing_unix(arg), 1);
}

bool	parse_argument(t_token *arg, char **envp)
{
	char	**tmp;
	int		i;
	int		j;

	token_initing(arg, envp);
	if (get_the_path(arg) == 0)
		return (0);
	if (arg->path == NULL)
		return (0);
	i = 0;
	tmp = ft_split(arg->content, ' ');
	while (tmp[i])
		i++;
	if (i == 0)
		return (0);
	arg->argz = (char **)malloc(sizeof(char *) * (i + 2));
	if (arg->argz == NULL)
		return (0);
	arg->argz[0] = arg->command;
	j = 0;
	while (++j <= i)
		arg->argz[j] = tmp[j];
	arg->argz[j] = NULL;
	free(tmp[0]);
	free(tmp);
	return (1);
}