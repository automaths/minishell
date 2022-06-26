#include "execution.h"

void	fill_input_before(t_command *cmd)
{
	int i;
	t_token *tmp;
	
	i = -1;
	tmp = cmd->redir;
	while (tmp != NULL)
	{
		if (tmp->place == 0 && is_redirection(tmp->content) == 1)
			cmd->fd_in[0][++i] = 4;
		tmp = tmp->next;
	}
}

void	fill_input_after(t_command *cmd)
{
	int i;
	t_token *tmp;
	
	i = -1;
	tmp = cmd->redir;
	while (tmp != NULL)
	{
		if (tmp->place == 1 && is_redirection(tmp->content) == 1)
			cmd->fd_in[1][++i] = 5;
		tmp = tmp->next;
	}
}

void	fill_output_before(t_command *cmd)
{
	int i;
	t_token *tmp;
	
	i = -1;
	tmp = cmd->redir;
	while (tmp != NULL)
	{
		if (tmp->place == 0 && is_redirection(tmp->content) == 2)
			cmd->fd_out[0][++i] = 6;
		tmp = tmp->next;
	}
}

void	fill_output_after(t_command *cmd)
{
	int i;
	t_token *tmp;
	
	i = -1;
	tmp = cmd->redir;
	while (tmp != NULL)
	{
		if (tmp->place == 1 && is_redirection(tmp->content) == 2)
			cmd->fd_out[1][++i] = 7;
		tmp = tmp->next;
	}
}
