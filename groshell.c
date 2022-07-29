/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:08 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/29 14:02:44 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void working_magic(char *str, t_env **env)
{
	t_command *cmd;
	t_first *uno;
	t_env *tmp;

	uno = step_one(str);
	if (uno != NULL && uno->next != NULL)
	{
		print_step_one(uno);
		if (command_validation(uno))
		{
			cmd = step_two(uno, *env);
			if (cmd != NULL)
			{
				// print_all(cmd);
				// if (!replace_all_variable(cmd, *env))
				// 	return ;
				tmp = exec_command(cmd);
				if (tmp != NULL)
					*env = tmp;
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_env		*env;

	(void)argc;
	(void)argv;
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
