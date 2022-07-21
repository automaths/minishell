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

#include "../execution.h"


int	main(int argc, char **argv, char **envp)
{
	int			count;
	char		*str;
	t_command	*cmd;
	t_first *uno;
	t_env *env;
	t_env *tmp;

	(void)argc;
	(void)argv;
	// env = env_to_list(envp);
	str = (char *)malloc(sizeof(char) * 4096);
	(void)envp;
	(void)env;
	(void)cmd;
	(void)tmp;
	while (1)
	{
		write(1, "groshell> ", 10);
		count = read(1, str, 4096);
		str[count] = '\0';
		if ((ft_strncmp(str, "exit", 4) == 0) && ft_strlen(str) == 5)
			break ;
		uno = step_one(str);
		if (uno != NULL)
		{
			printf("step one is success:\n");
			print_step_one(uno);
			// str = environning(str, env);
			// cmd = parse_line(str, env);
			// tmp = exec_command(cmd);
			// if (tmp != NULL)
			// 	env = tmp;
		}
	}
	return (0);
}
