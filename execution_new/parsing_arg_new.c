#include "../execution.h"

bool	get_the_path(t_command *cmd)
{
	int	i;
	char **envp;

	i = 0;
	envp = envp_to_char(cmd->env);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (0);
	cmd->arg->unix_paths = ft_split(&envp[i][4], ':');
	if (cmd->arg->unix_paths == NULL)
		return (0);
	if (command_trim(cmd) == 0)
		return (writing_error(NULL, CMD_NOT_FOUND), 0);
	if (cmd->arg->command == NULL)
		return (0);
	if (is_builts(cmd->arg->command))
		return (1);
	i = 0;
	while (cmd->arg->unix_paths[i] && find_path(cmd->arg, cmd->arg->unix_paths[i]) == 0)
		i++;
	if (cmd->arg->unix_paths[i] == NULL)
		return (writing_error(cmd->arg->command, CMD_NOT_FOUND), 0);
	if (cmd->arg->path == NULL)
		return (writing_error(cmd->arg->command, CMD_NOT_FOUND), 0);
	return (1);
}

bool	parse_argument(t_command *cmd)
{
	t_token *tmp_tkn;
	int		i;
	int		j;

	token_initing(cmd);
	if (get_the_path(cmd) == 0)
		return (0);
	i = 0;
	// tmp = ft_split(cmd->arg->content, ' ');
	// while (tmp[i])
		// i++;
    tmp_tkn = cmd->arg;
    while (tmp_tkn != NULL)
    {
        i++;        
        tmp_tkn = tmp_tkn->next;
    }
	if (i == 0)
		return (0);
	cmd->arg->argz = (char **)malloc(sizeof(char *) * (i + 2));
	if (cmd->arg->argz == NULL)
		return (0);
    tmp_tkn = cmd->arg;
	cmd->arg->argz[0] = cmd->arg->command;
    tmp_tkn = tmp_tkn->next;
	j = 0;
	while (++j < i)
    {
		cmd->arg->argz[j] = tmp_tkn->content;
        tmp_tkn = tmp_tkn->next;
    }
	cmd->arg->argz[j] = NULL;
	// free(tmp[0]);
	// free(tmp);
	return (1);
}
