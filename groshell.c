/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:08 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/30 13:37:32 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_all(t_command *cmd);

	//create a copy of env;
void	working_magic(char *str, t_env **env)
{
	t_command	*cmd;
	t_first		*uno;
	t_env		*tmp;

	uno = lexer(str);
	if (uno != NULL && uno->next != NULL)
	{
		if (command_validation(uno))
		{
			cmd = step_two(uno, *env);
			if (cmd != NULL)
			{
				// print_all(cmd);
				// (void)tmp;
				if (!replace_all_variable(cmd, *env))
					return ;
				tmp = exec_command(cmd);
				if (tmp != NULL)
					*env = tmp;
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_env	*env;

	(void)argc;
	(void)argv;
	singleton(0, 1);
	env = env_to_list(envp);
	str = (char *)malloc(sizeof(char) * 4096);
	while (1)
	{
		str = readline("groshell> ");
		add_history(str);
		if (!(ft_strncmp(str, "exit", 5)))
			break ;
		working_magic(str, &env);
	}
	return (0);
}
