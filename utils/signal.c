/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:43:44 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 14:22:57 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	exit_fork()
{
	write(1, "\n" ,1);
	singleton(130, 1);
	exit(0);
}

void	prompt_signal(int sig)
{
	(void)sig;
	singleton(130, 1);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signal(void)
{
	signal(SIGINT, prompt_signal);
}
