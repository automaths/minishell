/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:08 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/03 15:28:13 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "groshell.h"

void	print_all(t_command *cmd);
void	print_step_one(t_first *uno);

bool	check_spliting(char *str)
{
	int i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			return (1);
		if (is_whitespace(str[i]))
			return (1);
	}
	return (0);
}

t_token	*update_argz(t_token *arg, t_garbage **garbage)
{
	t_token *update;
	char	**split;
	int		i;
	
	update = NULL;
	split = ft_split(arg->content, ' ', garbage);
	i = -1;
	while (split[++i])
		add_back_tkn(&update, new_tkn(split[i], 0, garbage));
	return (update);
}

void	spliting_quotes(t_command *cmd)
{
	t_command *tmp;
	t_token *tnp;
	t_token *top;
	
	tmp = cmd;
	while (tmp != NULL)
	{
		if (check_spliting(tmp->arg->content))
		{
			tnp = tmp->arg->next;
			tmp->arg = update_argz(tmp->arg, cmd->garbage);
			top = tmp->arg;
			while (top != NULL)
				top = top->next;
			top = tnp;
		}
		tmp = tmp->next;
	}
}

void	working_magic(char *str, t_env **env, t_garbage **garbage)
{
	t_command	*cmd;
	t_first		*uno;

	uno = lexer(str, garbage);
	if (uno != NULL && uno->next != NULL)
	{
		if (command_validation(uno))
		{
			cmd = step_two(uno, *env, garbage);
			if (cmd != NULL)
			{
				if (!replace_all_variable(cmd, *env))
					return ;
				spliting_quotes(cmd);
				exec_command(cmd);
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_env		*env;
	t_garbage	*garbage;

	(void)argc;
	(void)argv;
	garbage = NULL;
	singleton(0, 1);
	env = env_to_list(envp, &garbage);
	while (1)
	{
		set_signal();
		str = readline("groshell> ");
		if (!str)
			return (clean_garbage(&garbage), printf("exit\n"), 0);
		add_history(str);
		if (!(ft_strncmp(str, "exit", 5)))
			break ;
		working_magic(str, &env, &garbage);
		free(str);
	}
	free(str);
	clean_garbage(&garbage);
	return (0);
}
