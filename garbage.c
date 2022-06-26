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

int	generate_fds(t_command *cmd)
{
	t_command *tmp;
	
	tmp = cmd;
	tmp->fd_in = (int **)malloc(sizeof(int*) * 3);
	if (tmp->fd_in == NULL)
		return (write(1, "malloc error", 12), 0);
	tmp->fd_in[2] = NULL;
	tmp->fd_in[0] = (int *)malloc(sizeof(int) * (input_before(cmd) + 1));
	if (tmp->fd_in[0] == NULL)
		return (write(1, "malloc error", 12), 0);
	tmp->fd_in[0][input_before(cmd)] = -10;
	fill_input_before(cmd);
	tmp->fd_in[1] = (int *)malloc(sizeof(int) * (input_after(cmd) + 1));
	if (tmp->fd_in[1] == NULL)
		return (write(1, "malloc error", 12), 0);
	tmp->fd_in[1][input_after(cmd)] = -10;
	fill_input_after(cmd);
	tmp->fd_out = (int **)malloc(sizeof(int*) * 3);
	if (tmp->fd_out == NULL)
		return (write(1, "malloc error", 12), 0);
	tmp->fd_out[2] = NULL;
	tmp->fd_out[0] = (int *)malloc(sizeof(int) * (output_before(cmd) + 1));
	if (tmp->fd_out[0] == NULL)
		return (write(1, "malloc error", 12), 0);
	tmp->fd_out[0][output_before(cmd)] = -10;
	fill_output_before(cmd);
	tmp->fd_out[1] = (int *)malloc(sizeof(int) * (output_after(cmd) + 1));
	if (tmp->fd_out[1] == NULL)
		return (write(1, "malloc error", 12), 0);
	tmp->fd_out[1][output_after(cmd)] = -10;
	fill_output_after(cmd);
	return (1);
}

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