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
		char c;
		c = singleton(0, 0) + '0';
		write(1, &c, 1);
	}
	return (0);
}
