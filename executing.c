#include "execution.h"

void	exec_token(t_command *cmd)
{
	cmd->arg->pid = fork();
	if (cmd->arg->pid == -1)
		return ;
	if (cmd->arg->pid == 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return ;
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return ;
		close(cmd->fd_in);
		close(cmd->fd_out);
		if (execve(cmd->arg->path, cmd->arg->argz, cmd->arg->envp) == -1)
			return ;
	}
	else
	{
		close(cmd->fd_in);
		close(cmd->fd_out);
	}
}

void	exec_command(t_command *cmd, char **envp)
{
	int i;
	t_command *tmp;

	if (!cmd)
		return ;
	tmp = cmd;
	redirectionning(tmp);
	print_all(tmp);

	i = 0;
	while (tmp != NULL)
	{
		parse_argument(tmp->arg, envp);
		print_parsed(tmp);
		write(1, "\nLAUCHING EXEC\n", 15);
		exec_token(tmp);
		write(1, "\nENDING EXEC\n", 13);
		tmp = tmp->next;
	}
	if (i != 1)
		tmp = cmd;
	while (tmp != NULL)
	{
		close(tmp->fd_in);
		close(tmp->fd_out);
		tmp = tmp->next;
	}
	
}