#include "../execution.h"

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

void	print_all(t_command *cmd)
{
	t_command	*tmp_cmd;
	t_token		*tmp_tkn;

	tmp_cmd = cmd;
	while (tmp_cmd != NULL)
	{
		tmp_tkn = tmp_cmd->arg;
		if (tmp_tkn != NULL)
		{
			writing ("the arg is :", tmp_tkn->content);
			tmp_tkn = tmp_tkn->next;
			while (tmp_tkn != NULL)
			{				
				writing ("with option :", tmp_tkn->content);
				tmp_tkn = tmp_tkn->next;
			}
		}
		tmp_tkn = tmp_cmd->redir;
		if (tmp_tkn != NULL)
		{
			write(1, "the redirection is a ", 21);
			if (tmp_tkn->type == WRITE)
				write(1, "write ", 6);
			if (tmp_tkn->type == HEREDOC)
				write(1, "heredoc ", 8);
			if (tmp_tkn->type == READ)
				write(1, "read ", 5);
			if (tmp_tkn->type == APPEND)
				write(1, "append ", 7);
			write(1, tmp_tkn->content, ft_strlen(tmp_tkn->content));
			tmp_tkn = tmp_tkn->next;
			while (tmp_tkn != NULL)
			{		
				write(1, "\n", 1);		
				write(1, "the next redirection is a ", 27);
				if (tmp_tkn->type == WRITE)
					write(1, "write ", 6);
				if (tmp_tkn->type == HEREDOC)
					write(1, "heredoc ", 8);
				if (tmp_tkn->type == READ)
					write(1, "read ", 5);
				if (tmp_tkn->type == APPEND)
					write(1, "append ", 7);
				write(1, tmp_tkn->content, ft_strlen(tmp_tkn->content));
				tmp_tkn = tmp_tkn->next;
			}
			write(1, "\n", 1);
		}
		if (tmp_cmd->next != NULL)
			writing("next command", " ");
		tmp_cmd = tmp_cmd->next;
	}
}

void	read_list(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->name);
		printf("%s\n", env->content);
		tmp = tmp->next;
	}
}

void print_step_one(t_first *uno)
{
	t_first	*tmp;

	tmp = uno;
	while (tmp != NULL)
	{
		if (tmp->type == APPEND)
		{
			write(1, "[APPEND] = ", 11);
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
		}
		if (tmp->type == WRITE)
		{
			write(1, "[WRITE] = ", 10);
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
		}
		if (tmp->type == HEREDOC)
		{
			write(1, "[HEREDOC] = ", 12);
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
		}
		if (tmp->type == READ)
		{
			write(1, "[READ] = ", 9);
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
		}
		if (tmp->type == PIPE)
		{
			write(1, "[PIPE] = ", 9);
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
		}
		if (tmp->type == WORD)
		{
			write(1, "[WORD] = ", 9);
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
		}
		if (tmp->type == BEGIN)
		{
			write(1, "[BEGIN] = ", 10);
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}
