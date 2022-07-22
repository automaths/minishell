#include "../execution.h"

t_env	*exec_command(t_command *cmd)
{
	t_command	*tmp;

	if (!cmd)
		return (NULL);
	tmp = cmd;
	if (redirectionning(tmp) == 0)
		return (NULL);
	while (tmp != NULL)
	{
		write(1, "COUCOU\n", 7);
		if (parse_argument(tmp) == 0)
		{
			if (tmp != NULL && tmp->next != NULL)
				tmp->next->fd_in = -1;
		}
		else
		{
			if (check_builts(tmp->arg->argz))
			{
				if (check_builts_nofork(tmp->arg->argz))
					exec_token_builts_nofork(tmp);
				else
					exec_token_builts(tmp);
			}
			else
				exec_token(tmp);
		}
		// print_parsed(cmd);
		print_fd(tmp->fd_in);
		print_fd(tmp->fd_out);
		tmp = tmp->next;
		if (tmp == NULL)
			break ;
	}
	waitpiding(cmd);
	closing_fd(cmd);
	// tmp = cmd;
	// while (tmp->next != NULL)
	// 	tmp = tmp->next;
	// return (tmp->env);
	return (NULL);
}