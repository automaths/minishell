#include "execution.h"

char	*quoting_ruling(char *str)
{
	int i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			str[i] = ' ';
			while (str[++i] && str[i] != '"')
			{
				if (str[i] == ' ')
					str[i] = '*';
			}
			str[i] = ' ';
		}
	}
	return (str);
}

char	**split_cleaning(char **split)
{
	int i;
	int j;
	
	i = -1;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
		{
			if (split[i][j] == '*')
				split[i][j] = ' ';
		}
	}
	return (split);
}
