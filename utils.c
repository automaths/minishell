#include "execution.h"

bool	is_arg(char *str)
{
	int i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == '<' && str[i] == '>' && str[i] == '|')
			return(0);
	}
	return (1);
}

bool	is_redirection(char *str)
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

bool	is_new_cmd(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (1);
	return (0);
}

