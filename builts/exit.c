/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimrod <nimrod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:07:06 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/07 19:05:47 by nimrod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// bool	is_exit(char c)
// {
// 	if (c == 'e' || c == 'x' || c == 'i' || c == 't')
// 		return (1);
// 	return (0);
// }

// int	find_exit_number(char *str)
// {
// 	int i;
	
// 	i = 0;
// 	while (is_whitespace2(str[i]))
// 		i++;
// 	while (is_exit(str[i]))
// 		i++;
// 	while (is_whitespace2(str[i]))
// 		i++;
// 	return (ft_atoi(&str[i]));
// }

// void	exec_exit(char *str)
// {
// 	int n;
	
// 	n = find_exit_number(str);
// 	exit(n);
// }

void	exec_exit(t_command *cmd)
{
	(void)cmd;
}
