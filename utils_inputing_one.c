#include "execution.h"

int	input_before(t_command *cmd)
{
	int i;
	t_token *tmp;
	
	i = 0;
	tmp = cmd->redir;
	while (tmp != NULL)
	{
		if (tmp->place == 0 && is_redirection(tmp->content) == 1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	input_after(t_command *cmd)
{
	int i;
	t_token *tmp;
	
	i = 0;
	tmp = cmd->redir;
	while (tmp != NULL)
	{
		if (tmp->place == 1 && is_redirection(tmp->content) == 1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	output_before(t_command *cmd)
{
	int i;
	t_token *tmp;
	
	i = 0;
	tmp = cmd->redir;
	while (tmp != NULL)
	{
		if (tmp->place == 0 && is_redirection(tmp->content) == 2)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	output_after(t_command *cmd)
{
	int i;
	t_token *tmp;
	
	i = 0;
	tmp = cmd->redir;
	while (tmp != NULL)
	{
		if (tmp->place == 1 && is_redirection(tmp->content) == 2)
			i++;
		tmp = tmp->next;
	}
	return (i);
}