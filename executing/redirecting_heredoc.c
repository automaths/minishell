/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:55:20 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 11:48:10 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool	reading_heredoc(char *limiter, int fd_in, t_garbage **garbage);

int	forking_heredoc(int fd_in, char *str, t_garbage **garbage)
{
	int	pid;

	str = ft_strtrim(str, "\"\'", garbage);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		signal(SIGINT, exit_fork);
		reading_heredoc(str, fd_in, garbage);
	}
	else
	{
		waitpid(pid, 0, 0);
		signal(SIGINT, prompt_signal);
	}
	return (0);
}

bool	heredoc_ception(char *str, t_garbage **garbage)
{
	str = ft_strtrim(str, " ", garbage);
	if (ft_strlen(str) < 3 || str[0] != '<' || str[1] != '<'\
		|| str[2] < 33 || str[2] > 126)
		return (0);
	return (1);
}

bool	reading_heredoc(char *limiter, int fd_in, t_garbage **garbage)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (!(ft_strncmp(str, limiter, ft_strlen(limiter))) \
			&& (ft_strlen(str) == ft_strlen(limiter)))
			break ;
		if (heredoc_ception(str, garbage))
			forking_heredoc(fd_in, ft_strtrim(str, "< ", garbage), garbage);
		else
		{
			write(fd_in, str, ft_strlen(str));
			write(fd_in, "\n", 1);
		}
	}
	exit(1);
}

int	opening_heredoc(char *content, t_garbage **garbage)
{
	int	fd[2];

	content = ft_strtrim(content, "<\"\'", garbage);
	if (pipe(fd) == -1)
		return (0);
	forking_heredoc(fd[1], content, garbage);
	close(fd[1]);
	return (fd[0]);
}
