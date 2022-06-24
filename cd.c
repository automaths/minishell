#include "execution.h"

bool	cd(char *arg)
{
	int fd;
	char *pwdz;
	char *path;
	
	pwdz = NULL;
	pwdz = getcwd(pwdz, 4096);
	
	if ((fd = open(arg, __O_DIRECTORY)) == -1)
		return (printf("%s is not a directory", arg), 0);
	close(fd);
	path = ft_strjoin(pwdz, "/");
	path = ft_strjoin(path, arg);
	pwd(1);
	printf("\n%s\n", path);
	chdir(path);
	pwd(1);
	return (1);
}
