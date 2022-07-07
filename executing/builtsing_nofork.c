#include "../execution.h"

bool	check_builts_nofork(char **argz)
{
	if (ft_strncmp(argz[0], "export", 7) == 0)
	{
		write(1, "nofork", 6);
		return (1);
	}
	return (0);
}

void	exec_token_builts_nofork(t_command *cmd)
{
	if (ft_strncmp(cmd->arg->argz[0], "export", 7) == 0)
		exec_export(cmd);
}
