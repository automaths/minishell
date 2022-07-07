#include "../execution.h"

void	print_all(t_command *cmd)
{
	int			i;
	t_command	*tmp;

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
		if (tmp->next != NULL)
			writing("next command", " ");
		tmp = tmp->next;
	}
}

void	read_list(t_env *env)
{
	t_env *tmp;
	
	tmp = env;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->name);
		printf("%s\n", env->content);
		tmp = tmp->next;
	}
}

void	writing_error(char *str, int num)
{
	if (num == 1)
	{
		write(2, "bash: ", 6);
		if (str != NULL)
			write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 20);
	}
	if (num == 2)
	{
		write(2, "bash: ", 6);
		if (str != NULL)
			write(2, str, ft_strlen(str));
		write(2, ": no such file or directory\n",
			ft_strlen(": no such file or directory\n"));
	}
	if (num == 3)
	{
		write(2, "bash: ", 6);
		if (str != NULL)
			write(2, str, ft_strlen(str));
		write(2, ": permission denied\n", ft_strlen(": permission denied\n"));
	}
}

void	writing(char *intro, char *content)
{
	write(1, "\n", 1);
	write(1, intro, ft_strlen(intro));
	write(1, content, ft_strlen(content));
	write(1, "\n", 1);
}

void	print_fd(int fd)
{
	char	c;

	c = fd + '0';
	write(1, "the fd is :", 11);
	write(1, &c, 1);
	write(1, "\n", 1);
}

void	print_parsed(t_command *cmd)
{
	t_token		*tmp;
	int			i;

	tmp = cmd->arg;
	if (cmd->arg != NULL)
	{
		if (tmp->content != NULL)
			writing("the content is:", tmp->content);
		if (tmp->command != NULL)
			writing("the command is:", tmp->command);
		if (tmp->path != NULL)
			writing("the path is:", tmp->path);
		i = -1;
		while (tmp->argz[++i])
			writing("the argz is : ", tmp->argz[i]);
	}
}
