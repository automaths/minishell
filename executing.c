#include "execution.h"

bool	first_command(t_struct *dd)
{
	dd->c = 2;
	if (parse_arguments(dd) == 0)
		return (0);
	if (access(dd->argv[1], F_OK) == -1)
		return (freeing_path_and_argz(dd),
			ft_printf("infile doesn't exist"), 0);
	if (access(dd->argv[1], R_OK) == -1)
		return (freeing_path_and_argz(dd),
			ft_printf("infile wrong permissions"), 0);
	dd->fd_infile = open(dd->argv[1], O_RDONLY);
	if (dd->fd_infile == -1)
		return (freeing_path_and_argz(dd),
			ft_printf("can't open input file"), 0);
	if (pipe(dd->fd[dd->c]) == -1)
		return (ft_printf("can't open pipe"), 0);
	forking(dd, dd->fd_infile, dd->fd[dd->c][1], dd->pid[dd->c]);
	return (1);
}

bool	last_command(t_struct *dd)
{
	dd->c = dd->argc - 2;
	if (parse_arguments(dd) == 0)
		return (0);
	if (pipe(dd->fd[dd->c]) == -1)
		return (ft_printf("can't open pipe"), 0);
	forking(dd, dd->fd[dd->c - 1][0], dd->fd[dd->c][1], dd->pid[dd->c]);
	return (1);
}

bool	looping_commands(t_struct *dd)
{
	dd->c++;
	while (dd->c < dd->argc - 2)
	{
		if (parse_arguments(dd) == 0)
			return (0);
		if (pipe(dd->fd[dd->c]) == -1)
			return (freeing_path_and_argz(dd), ft_printf("can't open pipe"), 0);
		forking(dd, dd->fd[dd->c - 1][0], dd->fd[dd->c][1], dd->pid[dd->c]);
		freeing_path_and_argz(dd);
		dd->c++;
	}
	return (1);
}



void	exec_command(t_command *cmd, char **envp)
{
	t_command *tmp;

	if (!cmd)
		return ;
	tmp = cmd;
	while (tmp != NULL)
	{
		parse_argument(tmp->arg, envp);
		print_parsed(tmp);
		print_all(tmp);
		write(1, "\nLAUCHING EXEC\n", 15);
		exec_token(tmp);
		write(1, "\nENDING EXEC\n", 13);
		tmp = tmp->next;
	}
	
}