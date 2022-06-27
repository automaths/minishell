#include "execution.h"

// void	infiling(t_command *cmd)
// {
// 	if (access("infile", F_OK) == -1)
// 		return (freeing_path_and_argz(cmd),
// 			ft_printf("infile doesn't exist"), 0);
// 	if (access("infile", R_OK) == -1)
// 		return (freeing_path_and_argz(cmd),
// 			ft_printf("infile wrong permissions"), 0);
// 	cmd->fd_in = open("infile", O_RDONLY);
// 	if (cmd->fd_in == -1)
// 		return (freeing_path_and_argz(cmd),
// 			ft_printf("can't open input file"), 0);
// }

// bool	first_command(t_command *cmd)
// {

// 	if (pipe(cmd->fd[cmd->c]) == -1)
// 		return (ft_printf("can't open pipe"), 0);
// 	forking(cmd, cmd->fd_infile, cmd->fd[cmd->c][1], cmd->pid[cmd->c]);
// 	return (1);
// }

// bool	last_command(t_command *cmd)
// {
// 	cmd->c = cmd->argc - 2;
// 	if (parse_arguments(cmd) == 0)
// 		return (0);
// 	if (pipe(cmd->fd[cmd->c]) == -1)
// 		return (ft_printf("can't open pipe"), 0);
// 	forking(cmd, cmd->fd[cmd->c - 1][0], cmd->fd[cmd->c][1], cmd->pid[cmd->c]);
// 	return (1);
// }

// //VARIABLE A ACTUALISER
// void	forking(t_command *cmd, int fd_in, int fd_out, int pid)
// {
// 	pid = fork();
// 	if (pid == -1)
// 		exiting("can't fork");
// 	if (pid == 0)
// 	{
// 		if (dup2(fd_in, STDIN_FILENO) == -1)
// 			exiting(cmd->arg->argz[0]);
// 		if (dup2(fd_out, STDOUT_FILENO) == -1)
// 			exiting(cmd->arg->argz[0]);
// 		close(fd_in);
// 		close(fd_out);
// 		if (execve(cmd->arg->path, cmd->arg->argz, cmd->arg->envp) == -1)
// 			exiting(cmd->arg->argz[0]);
// 	}
// 	else
// 	{
// 		close(fd_in);
// 		close(fd_out);
// 	}
// }

// bool	looping_commands(t_command *cmd)
// {
// 	cmd->c++;
// 	while (cmd->c < cmd->argc - 2)
// 	{
// 		if (parse_arguments(cmd) == 0)
// 			return (0);
// 		if (pipe(cmd->fd[cmd->c]) == -1)
// 			return (freeing_path_and_argz(cmd), ft_printf("can't open pipe"), 0);
// 		forking(cmd, cmd->fd[cmd->c - 1][0], cmd->fd[cmd->c][1], cmd->pid[cmd->c]);
// 		freeing_path_and_argz(cmd);
// 		cmd->c++;
// 	}
// 	return (1);
// }

// void	forking_redir(char *path, char **arg, char **envp, int fd_in, int fd_out, pid_t pid)
// {
// 	pid = fork();
// 	if (pid == -1)
// 		return ;
// 	if (pid == 0)
// 	{
// 		if (dup2(fd_in, STDIN_FILENO) == -1)
// 			return ;
// 		if (dup2(fd_out, STDOUT_FILENO) == -1)
// 			return ;
// 		close(fd_in);
// 		close(fd_out);
// 		if (execve(path, arg, envp) == -1)
// 			return ;
// 	}
// }

// void	redirectioning(t_command *cmd)
// {
// 	t_token *tmp;
	
// 	tmp = cmd->redir;
// 	if (tmp != NULL)
// 	{
// 		//FAIRE QQCH AVEC LES DUPS
// 	}
// }

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
	t_command *tmp;

	if (!cmd)
		return ;
	tmp = cmd;
	(void)envp;
	// infiling(cmd);
	redirectionning(tmp);
	print_all(tmp);

	while (tmp != NULL)
	{
		parse_argument(tmp->arg, envp);
		print_parsed(tmp);
		write(1, "\nLAUCHING EXEC\n", 15);
		exec_token(tmp);
		write(1, "\nENDING EXEC\n", 13);
		tmp = tmp->next;
	}
	
}