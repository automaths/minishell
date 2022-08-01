/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:26:02 by nsartral          #+#    #+#             */
/*   Updated: 2022/08/01 12:05:38 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool	check_fd_in(char *content, t_garbage **garbage)
{
	content = ft_strtrim(content, "< ", garbage);
	if (access(content, F_OK) != 0)
		return (writing_error(ft_strtrim(content, "> ", garbage), NO_FILE), 0);
	if (access(content, R_OK) == -1)
		return (writing_error(ft_strtrim(content, "> ", garbage) \
			, WRONG_CHMOD), 0);
	return (1);
}

bool	check_fd_out(t_token *redir, t_garbage **garbage)
{
	int		fd;
	char	*file;

	file = ft_strtrim(redir->content, "> ", garbage);
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return (writing_error(ft_strtrim(file, "> ", garbage) \
				, WRONG_CHMOD), 0);
	}
	if (redir != NULL)
	{
		if (redir->type == APPEND)
			fd = open(file, O_CREAT | O_RDWR, 0644);
		if (redir->type == WRITE)
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			return (writing("cant open file", " "), 0);
		close(fd);
	}
	return (1);
}

t_token	*last_redir(t_command *cmd)
{
	t_token	*tmp;
	t_token	*the_one;

	tmp = cmd->redir;
	the_one = NULL;
	while (tmp != NULL)
	{
		if (tmp->type == APPEND || tmp->type == WRITE)
		{
			if (check_fd_out(tmp, cmd->garbage) == 0)
				return (0);
			the_one = tmp;
		}
		tmp = tmp->next;
	}
	return (the_one);
}
