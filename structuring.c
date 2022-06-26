# include "execution.h"

t_command	*parse_line(char *str)
{
	char **split;
	char *str_quoted;
	t_command *cmd;
	t_command *tmp;
	int i;
	int t;
	
	str_quoted = quoting_ruling(str);
	split = ft_split(str_quoted, ' ');
	if (split == NULL)
		return (NULL);
	split = split_cleaning(split);

	i = -1;
	t = 0;
	cmd = new_cmd(i);
	tmp = cmd;
	while(split[++i])
	{
		if (is_arg(split[i]))
		{
			add_back_tkn(&tmp->arg, new_tkn(split[i]), -1);
			t = 1;
		}
		if (is_redirection(split[i]))
		{
			add_back_tkn(&tmp->redir, new_tkn(split[i]), t);
		}
		if (is_new_cmd(split[i]))
		{
			add_back_cmd(&tmp, new_cmd(i));
			t = 0;
			tmp = tmp->next;
		}
	}
	return (cmd);
}
