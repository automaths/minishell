#include "execution.h"

void	exec_builts(t_command *cmd)
{
	write(1, "\n", 1);
	write(1, "using builts", ft_strlen("using builts"));
	write(1, "\n", 1);
	if (ft_strncmp(cmd->arg->argz[0], "echo", 5) == 0)
		exec_echo(cmd);
	// if (ft_strncmp(cmd->arg->argz[0], "cd", 3) == 0)
	// 	exec_cd(content, env);
	if (ft_strncmp(cmd->arg->argz[0], "pwd", 4) == 0)
		exec_pwd(cmd->arg->envp);
	if (ft_strncmp(cmd->arg->argz[0], "export", 7) == 0)
		exec_export(cmd);
	// if (ft_strncmp(cmd->arg->argz[0], "unset", 6) == 0)
	// 	exec_unset(content, env);
	if (ft_strncmp(cmd->arg->argz[0], "env", 4) == 0)
		exec_env(cmd->arg->envp);
	// if (ft_strncmp(cmd->arg->argz[0], "exit", 5) == 0)
	// 	exec_exit(content);
	exit(0);
}

bool	check_builts(char **argz)
{
	if (ft_strncmp("echo", argz[0], 5) == 0)
		return (1);
	if (ft_strncmp("env", argz[0], 4) == 0)
		return (1);
	if (ft_strncmp("pwd", argz[0], 4) == 0)
		return (1);
	if (ft_strncmp(argz[0], "export", 7) == 0)
		return (1);
	return (0);
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
	exec_builts(cmd);
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