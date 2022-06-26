#include "execution.h"

int	count_out(t_command *cmd)
{
	int i;
	t_token *tmp;
	
	tmp = cmd->redir;

	if (tmp != NULL)
	{
		i = 0;
		while (tmp != NULL)
		{				
			if (tmp->content != NULL)
			{
				if (is_redirection(tmp->content) == 2)
					i++;
			}
			tmp = tmp->next;
		}
	}
	return (i);
}

int	count_in(t_command *cmd)
{
	int i;
	t_token *tmp;
	
	tmp = cmd->redir;

	if (tmp != NULL)
	{
		i = 0;
		while (tmp != NULL)
		{				
			if (tmp->content != NULL)
			{
				if (is_redirection(tmp->content) == 1)
					i++;
			}
			tmp = tmp->next;
		}
	}
	return (i);
}
