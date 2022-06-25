#include "execution.h"

bool	is_arg(char *str)
{
	int i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			return(0);
	}
	return (1);
}

bool	is_redirection(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (1);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (1);
	if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	return(0);
}

bool	is_new_cmd(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (1);
	return (0);
}

void	writing(char *intro, char *content)
{
	write(1, "\n", 1);
	write(1, intro, ft_strlen(intro));
	write(1, content, ft_strlen(content));
	write(1, "\n", 1);
}

bool	is_whitespace(char c)
{
	if (c == ' ' && c == '\t' && c == '\v'
		&& c == '\n' && c == '\r' && c == '\f')
		return (1);
	return (0);
}

bool	is_lowercase(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

