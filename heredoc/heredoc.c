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

int	ft_strlen(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (one[i] && two[i] && one[i] == two[i] && i < n - 1)
		i++;
	return (one[i] - two[i]);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

bool	reading_heredoc(char **argv, int fd_in)
{
	char	*str;

	(void)argv;
	(void)fd_in;
	str = (char *)malloc(sizeof(char) * 4096);
	while (1)
	{
		str = readline("groshell> ");
		if (!(ft_strncmp(str, "exit", 5)))
			break ;
		write(fd_in, str, ft_strlen(str));
	}
	exit(1);
}

int	forking_heredoc(char **argv)
{
	int fd[2];
	int pid;
	if (pipe(fd) == -1)
		return (0);
	// if (dup2(STDIN_FILENO, fd[1]) == -1)
	// 	return (0);
	// if (dup2(fd[1], STDOUT_FILENO) == -1)
	// 	return (0);
	// close (STDIN_FILENO);
	// close(STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		reading_heredoc(argv, fd[1]);
	}
	waitpid(pid, 0, 0);
	char *str;
	int count;
	str = (char *)malloc(sizeof(char) * 4096);
	if (str == NULL)
		return (0);
	count = read(fd[0], str, 4096);
	str[count] = '\0';
	write(1, str, ft_strlen(str));
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	// if (argc != 2)
	// 	return (0);
	forking_heredoc(argv);
	// reading_heredoc(argv, 0);
	return (0);
}
