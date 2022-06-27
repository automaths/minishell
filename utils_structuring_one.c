#include "execution.h"

t_command	*new_cmd(int i)
{
	t_command	*new;

	(void)i;
	new = (t_command *)malloc(sizeof(t_command));
	if (new == NULL)
		return (NULL);
	new->fd_in = -1;
	new->fd_out = -1;
	new->is_piped = 0;
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
