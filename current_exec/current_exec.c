# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "errno.h"

// if (access(filename, F_OK|X_OK) == 0)
// {
//     /* You can execute this file. */
// }

// void	forking(t_command *cmd)
// {
// 	if (cmd->fd_in != 0)
// 	{
// 		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
// 			return ;
// 	}
// 	if (cmd->fd_out != 1)
// 	{
// 		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
// 			return ;
// 	}
// 	if (cmd->fd_in != 0)
// 		close(cmd->fd_in);
// 	if (cmd->fd_out != 1)
// 		close(cmd->fd_out);
// 	if (execve(cmd->arg->path, cmd->arg->argz, cmd->envp_char) == -1)
// 		return ;
// }

// void	exec_token(t_command *cmd)
// {
// 	cmd->envp_char = envp_to_char(cmd->env);
// 	cmd->arg->pid = fork();
// 	if (cmd->arg->pid == -1)
// 		return ;
// 	if (cmd->arg->pid == 0)
// 		forking(cmd);
// 	else
// 	{
// 		if (cmd->fd_in != 0)
// 			close(cmd->fd_in);
// 		if (cmd->fd_out != 1)
// 			close(cmd->fd_out);
// 	}
// }

bool	is_whitespace2(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\n' || c == '\r' || c == '\f')
		return (1);
	return (0);
}

bool	is_printable_except_space(char c)
{
	if (c < 33 || c > 126)
		return (0);
	return (1);
}


bool	check_local_exec(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && is_whitespace2(str[i]))
		;
	if (str[i] && str[i] == '.' && str[i + 1] && str[i + 1] == '/' && str[i + 2] && is_printable_except_space(str[i + 2]))
		return (1);
	return (0);

}

void	launch_local_exec(char *str, char **envp)
{
	char **exec;

	(void)str;
	exec = (char **)malloc(sizeof(char *) * 2);
	exec[0] = (char *)malloc(sizeof(char) * strlen("./a.out"));
	exec[1] = NULL;
	
	execve("./test", exec, envp);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	if (check_local_exec(argv[1]))
		launch_local_exec(argv[1], envp);
	return (0);
}