#include "execution.h"

void	freeing_unix(t_token *arg)
{
	(void)arg;
	// int	i;

	// i = -1;
	// while (arg->unix_paths[++i])
	// 	free(arg->unix_paths[i]);
	// if (arg->unix_paths)
	// 	free(arg->unix_paths);
}

void	freeing_command(t_token *arg)
{
	(void)arg;
	// if (arg->command)
	// 	free(arg->command);
}

void	freeing_path(t_token *arg)
{
	(void)arg;
	// if (arg->path)
	// 	free(arg->path);
}

void	freeing_argz(t_token *arg)
{
	(void)arg;
	// int	i;

	// i = -1;
	// while (arg->argz[++i])
	// 	free(arg->argz[i]);
	// if (arg->argz)
	// 	free(arg->argz);
}

void	freeing_path_and_argz(t_token *arg)
{
	(void)arg;
	// freeing_argz(arg);
	// freeing_path(arg);
}
