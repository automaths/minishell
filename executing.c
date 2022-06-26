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

void	piping(t_command *cmd)
{
	(void)cmd;
}

void	exec_token(t_command *cmd)
{
	(void)cmd;
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

void	redirectionning(t_command *cmd)
{
	t_command *tmp;
	
	tmp = cmd;
	while (tmp != NULL)
	{	
		generate_fds(cmd);

		tmp = tmp->next;
	}
}

void	exec_command(t_command *cmd, char **envp)
{
	t_command *tmp;

	if (!cmd)
		return ;
	tmp = cmd;
	// (void)tmp;
	// (void)cmd;
	(void)envp;
	// infiling(cmd);
	redirectionning(tmp);
	print_all(tmp);
	// piping(tmp);
	// print_parsed(tmp);
	// print_all(tmp);
	while (tmp != NULL)
	{
		parse_argument(tmp->arg, envp);
		write(1, "\nLAUCHING EXEC\n", 15);
		exec_token(tmp);
		write(1, "\nENDING EXEC\n", 13);
		tmp = tmp->next;
	}
	
}