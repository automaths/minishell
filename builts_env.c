#include "execution.h"

void	exec_env(t_command *cmd)
{
	t_env *tmp;
	
	tmp = cmd->envp;
	while (tmp != NULL)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, "=", 1);
		write(1, tmp->content, ft_strlen(tmp->content));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}