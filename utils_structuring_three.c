#include "execution.h"

char	*quoting_ruling(char *str)
{
	char *new;
	int i;
	int t;
	
	i = -1;
	t = 0;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
			{
				if (str[i] == ' ')
					str[i] = '*';
			}
			t = 1;
		}
	}
	if (t == 1)
	{
		new = (char *)malloc(sizeof(char) * (ft_strlen(str) - 3));
		if (new == NULL)
			return (NULL);
		i = -1;
		while ((size_t)++i < (ft_strlen(str) - 3))
		{
			new[i] = str[i + 1];
		}
		new[i] = '\0';
		free(str);
		return (new);
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
