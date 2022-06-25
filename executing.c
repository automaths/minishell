#include "execution.h"


void	last_exec(t_command *cmd, char **envp)
{
	parse_argument(cmd->arg, envp);
	//parse_redirection(cmd->redir);
}




void	exec_command(t_command *cmd, char **envp)
{
	// t_command *tmp;
	
	// while (tmp->next != NULL)
	// {
	// 	piping(tmp);
	// 	tmp = tmp->next;	
	// }
	last_exec(cmd, envp);
}