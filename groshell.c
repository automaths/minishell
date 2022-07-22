/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:08 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/08 08:35:01 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void working_magic(char *str, t_env **env)
{
	t_command *cmd;
	t_first *uno;
	t_env *tmp;

	uno = step_one(str);
	if (uno->next != NULL)
	{
		printf("step one is success:\n");
		// print_step_one(uno);
		if (command_validation(uno))
		{
			cmd = step_two(uno, *env);
			if (cmd != NULL)
			{
				// print_all(cmd);
				tmp = exec_command(cmd);
				if (tmp != NULL)
					*env = tmp;
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int			count;
	char		*str;
	t_env		*env;

	(void)argc;
	(void)argv;
	env = env_to_list(envp);
	str = (char *)malloc(sizeof(char) * 4096);
	while (1)
	{
		write(1, "groshell> ", 10);
		count = read(1, str, 4096);
		str[count] = '\0';
		if ((ft_strncmp(str, "exit", 4) == 0) && ft_strlen(str) == 5)
			break ;
		working_magic(str, &env);
	}
	return (0);
}
