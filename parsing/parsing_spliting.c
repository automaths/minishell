#include "../execution.h"

char	**spliting_plus(char *str)
{
	char	*str_quoted;
	char	**split;

	str_quoted = quoting_ruling(str);
	split = ft_split(str_quoted, ' ');
	if (split == NULL)
		return (NULL);
	split = split_cleaning(split);
	return (split);
}

char	*quoting_ruling(char *str)
{
	int	i;

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
	int	i;
	int	j;

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

t_command	*parse_line(char *str, t_env *env)
{
	char			**split;
	t_command		*cmd;
	t_command		*tmp;
	int				i;

	split = spliting_plus(str);
	i = -1;
	cmd = new_cmd(i, env);
	tmp = cmd;
	while (split[++i])
	{
		if (is_arg(split[i]))
			add_back_tkn(&tmp->arg, new_tkn(split[i]));
		if (is_redirection(split[i]))
			add_back_tkn(&tmp->redir, new_tkn(split[i]));
		if (is_new_cmd(split[i]))
		{
			add_back_cmd(&tmp, new_cmd(i, env));
			tmp = tmp->next;
		}
	}
	return (cmd);
}
