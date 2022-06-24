#include "../execution.h"

void	pwd(int fd)
{
	char *pwd;
	
	pwd = NULL;
	pwd = getcwd(pwd, 4096);
	write(fd, pwd, ft_strlen(pwd));
}