#include "execution.h"

bool	check_builts(char **argz)
{
	if (ft_strncmp("echo", argz[0], 4) == 0)
		return (1);
	return (0);
}