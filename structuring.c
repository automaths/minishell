# include "execution.h"

t_command	*parse_line(char *str, char **envp)
{
	int i;
	int j;
	t_command *cmd;
	t_command *tmp;
	char **split;

	(void)j;
	(void)envp;
	
	split = ft_split(str, ' ');
	if (split == NULL)
		return (NULL);

	i = -1;
	cmd = new_cmd(0, 0);
	tmp = cmd;
	while(split[++i])
	{
		if (is_arg(split[i]))
			add_back_tkn(&tmp->arg, new_tkn(split[i]));
		if (is_redirection(split[i]))
			add_back_tkn(&tmp->redir, new_tkn(split[i]));
		if (is_new_cmd(split[i]))
		{
			add_back_cmd(&tmp, new_cmd(0, 0));
			tmp = tmp->next;
		}
	}
	return (cmd);
}
