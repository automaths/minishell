#include "execution.h"

bool	check_redirection(char *str)
{
	if (ft_strncmp(str, ">>", 3) == 0)
		return (1);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (1);
	if (ft_strncmp(str, ">", 2) == 0)
		return (1);
	if (ft_strncmp(str, "<", 2) == 0)
		return (1);
	return(0);
}

bool	check_pipe(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)envp;

	
	
	return (0);
}