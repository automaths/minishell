#include "execution.h"

void	env(int fd, char **envp)
{
	int i;

	i = -1;
	while (envp[++i])
	{
		write(fd, envp[i], ft_strlen(envp[i]));
		write(fd, "\n", 1);
	}
}