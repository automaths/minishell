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

int	singleton(int set, bool write)
{

	static int singleton = 0;
	if (write)
		singleton = set;
	return (singleton);
}

int	ft_strlen(char *str)
{
	int i = -1;
	while (str[++i])
		;
	return (i);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(1, "\n", 1);
	// exit(singleton(0, 0));
}

int	main(void)
{
	char *str;
	str = (char *)malloc(sizeof(char) * 4096);
	while (1)
	{
		str = readline("singleton> ");
		if (!(strncmp(str, "exit", 5)))
			break ;
		singleton(atoi(str), 1);
		ft_error(strerror(singleton(0, 0)));
	}
	return (0);
}
		// ft_error(strerror(errno));