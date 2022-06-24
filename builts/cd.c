#include "../execution.h"

bool	cd(char *arg)
{
	int fd;
	char *pwdz;
	char *path;
	
	pwdz = NULL;
	pwdz = getcwd(pwdz, 4096);
	if ((fd = open(arg, __O_DIRECTORY)) == -1)
		return (printf("\n%s is not a directory", arg), 0);
	close(fd);
	path = ft_strjoin(pwdz, "/");
	path = ft_strjoin(path, arg);
	chdir(path);
	return (1);
}
