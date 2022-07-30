#include "../execution.h"

bool	reading_heredoc(char *limiter, int fd_in);

int	forking_heredoc(int fd_in, char *str)
{
	int pid;
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		reading_heredoc(str, fd_in);
	}
	waitpid(pid, 0, 0);
	return (0);
}

bool	reading_heredoc(char *limiter, int fd_in)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 4096);
	while (1)
	{
		str = readline("> ");
		if (!(ft_strncmp(str, limiter, 5)))
			break ;
		if (ft_strncmp(str, "new", 4))
		{
			write(fd_in, str, ft_strlen(str));
			write(fd_in, "\n", 1);
		}
		else
			forking_heredoc(fd_in, "quit");
	}
	exit(1);
}

int	opening_heredoc(char *content)
{
	(void)content;
	int fd[2];
	if (pipe(fd) == -1)
		return (0);
	forking_heredoc(fd[1], "exit");
	close(fd[1]);
	// close fd[1];
	return (fd[0]);
}