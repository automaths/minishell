#include "execution.h"

// typedef struct s_command {
// 	char **arg;
//	int nb_argz;
// 	int **redirection;
//	int nb_redirection;
// 	int fd_in;
// 	int fd_out;
// 	t_command *next;
// } t_command;

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

int	count_argz(int argc, char **argv)
{
	int i;
	int n;
	
	i = -1;
	n = 0;
	while (++i < argc)
	{
		if (check_redirection(argv[i]))
			n++;
	}
	return (n);
}

int	count_redirections(int argc, char **argv)
{
	int i;
	int n;
	
	i = -1;
	n = 0;
	while (++i < argc)
	{
		if (check_redirection(argv[i]))
			n++;
	}
	return (n);
}

int	main(int argc, char **argv, char **envp)
{
	int i;
	int j;
	// t_command command;
	(void)argc;
	(void)envp;
	
	i = count_redirections(argc, argv);
	j = count_argz(argc, argv);
	
	
	return (0);
}