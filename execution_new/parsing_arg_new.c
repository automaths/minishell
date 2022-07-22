#include "../execution.h"

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
