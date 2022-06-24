#include "../execution.h"

void	echo(int fd, int mode, char *str)
{
	write(fd, str, ft_strlen(str));
	if (mode == 0)
		write(fd, "\n", 1);
}
