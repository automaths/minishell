#include "execution.h"

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

void	print_all(t_command *cmd)
{
	int i;
	t_command *tmp;
	
	tmp = cmd;
	while (tmp != NULL)
	{
		if (tmp->arg != NULL)
		{
			writing ("the arg is :", tmp->arg->content);
			if (tmp->arg->argz != NULL)
			{
				i = -1;
				while (tmp->arg->argz[++i])
					writing ("with option :", tmp->arg->argz[i]);
			}
		}
		if (tmp->redir != NULL)
		{
			writing ("the redirection is :", tmp->redir->content);
			tmp->redir = tmp->redir->next;
			while (tmp->redir != NULL)
			{				
				writing ("next redirection is :", tmp->redir->content);
				tmp->redir = tmp->redir->next;
			}
		}
		writing("trying next command", " ");
		tmp = tmp->next;
	}
}

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

int	is_redirection(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (1);
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(str, ">", 1) == 0)
		return (2);
	return(0);
}

bool	is_new_cmd(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (1);
	return (0);
}
