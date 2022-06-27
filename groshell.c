/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:08 by nsartral          #+#    #+#             */
/*   Updated: 2022/06/27 12:35:12 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	main(int argc, char **argv, char **envp)
{
	int			count;
	char		*str;
	t_command	*cmd;

	(void)argc;
	(void)argv;
	str = (char *)malloc(sizeof(char) * 4096);
	while (1)
	{
		write(1, "> ", 2);
		count = read(1, str, 4096);
		str[count] = '\0';
		if ((ft_strncmp(str, "exit", 4) == 0) && ft_strlen(str) == 5)
			break ;
		cmd = parse_line(str);
		exec_command(cmd, envp);
	}
	return (0);
}
