#include "execution.h"

void	exec_echo(t_command *cmd)
{
	int i;
	
	i = 0;
	write(1, "Using built in", ft_strlen("using built in"));
	while (cmd->arg->argz[++i])
	{
		write(1, cmd->arg->argz[i], ft_strlen(cmd->arg->argz[i]));
		write(1, " ", 1);
	}
	exit(0);
}

void	forking_builts(t_command *cmd)
{
	if (cmd->fd_in != 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return ;
	}
	if (cmd->fd_out != 1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return ;
	}
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	exec_echo(cmd);
}

void	exec_token_builts(t_command *cmd)
{
	cmd->arg->pid = fork();
	if (cmd->arg->pid == -1)
		return ;
	if (cmd->arg->pid == 0)
		forking_builts(cmd);
	else
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
	}
}