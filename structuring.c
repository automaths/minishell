# include "execution.h"

t_command	*new_cmd(int fd_in, int fd_out)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (new == NULL)
		return (NULL);
	new->fd_in = fd_in;
	new->fd_out = fd_out;
	new->next = NULL;
	return (new);
}

t_token	*new_tkn(char *arg)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->content = arg;
	new->next = NULL;
	return (new);
}

void	add_back_tkn(t_token **tkn, t_token *new)
{
	t_token	*tmp;

	if (*tkn)
	{
		tmp = *tkn;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (tkn)
		*tkn = new;
}


int	count_commands(char *str)
{
	int i;
	int j;
	
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			++j;
	}
	return (j);
}

void	parse_line(char *str, char **envp)
{
	int i;
	int j;
	t_command *cmd;
	char **split;

	(void)j;
	(void)envp;
	
	split = ft_split(str, ' ');
	if (split == NULL)
		return (printf("malloc error"), 0);
	
	i = -1;
	cmd = new_cmd(0, 0);
	while(split[i])
	{
		if (is_arg(split[i]))
			add_back_tkn(&cmd->arg, new_tkn(split[i]));
		if (is_redirection(split[i]))
			add_back_tkn(&cmd->arg, new_tkn(split[i]));
			
		
	}
}
