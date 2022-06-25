# include "execution.h"

int	count_commands(char *str)
{
	int i;
	int j;
	
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			++j;
	}
	return (j);
}

void	parse_line(char *str, char **envp)
{
	int i;
	int j;
	t_command *cmd;
	char **split;

	(void)j;
	(void)envp;
	
	split = ft_split(str, ' ');
	if (split == NULL)
		return (printf("malloc error"), 0);
	
	i = -1;
	cmd = 
	while(split[i])
	{
		
		
	}
}
