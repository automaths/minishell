/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:08 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/31 17:13:30 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_all(t_command *cmd);
void	print_step_one(t_first *uno);

void	working_magic(char *str, t_env **env, t_garbage **garbage)
{
	t_command	*cmd;
	t_first		*uno;

	uno = lexer(str, garbage);
	if (uno != NULL && uno->next != NULL)
	{
		if (command_validation(uno))
		{
			cmd = step_two(uno, *env);
			if (cmd != NULL)
			{
				if (!replace_all_variable(cmd, *env))
					return ;
				exec_command(cmd);
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_env	*env;
	t_garbage	*garbage;

	(void)argc;
	(void)argv;
	garbage = NULL;
	singleton(0, 1);
	env = env_to_list(envp);
	str = (char *)malloc(sizeof(char) * 4096);
	while (1)
	{
		str = readline("groshell> ");
		add_history(str);
		if (!(ft_strncmp(str, "exit", 5)))
			break ;
		working_magic(str, &env, &garbage);
	}
	// clean_garbage(&garbage);
	return (0);
}
