# include "execution.h"

t_command	*new_cmd(int fd_in, int fd_out)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (new == NULL)
		return (NULL);
	new->fd_in = fd_in;
	new->fd_out = fd_out;
	new->arg = NULL;
	new->redir = NULL;
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

void	add_back_cmd(t_command **cmd, t_command *new)
{
	t_command	*tmp;

	if (*cmd)
	{
		tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (cmd)
		*cmd = new;
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

void	print_all(t_command *cmd)
{
	t_command *tmp;
	
	tmp = cmd;
	while (tmp != NULL)
	{
		if (tmp->arg != NULL)
			writing ("the arg is :", tmp->arg->content);
		if (tmp->redir != NULL)
			writing ("the redirection is :", tmp->redir->content);
		writing("trying next command", " ");
		tmp = tmp->next;
	}
}

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
