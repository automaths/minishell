/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:46:55 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/29 15:47:04 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

bool    redirection_validation(t_first *uno)
{
    t_first *tmp;

    tmp = uno->next;
    while (tmp != NULL)
    {
        if (tmp->type == APPEND || tmp->type == WRITE || tmp->type == READ || tmp->type == HEREDOC)
        {
            if (!tmp->next || tmp->next->type != WORD)
                return (0);
        }
        tmp = tmp->next;
    }
    return (1);
}

bool    pipes_validation(t_first *uno)
{
    t_first *tmp;

    tmp = uno->next;
    if (tmp != NULL && tmp->type == PIPE)
        return (0);
    while (tmp != NULL)
    {
        if (tmp->type == PIPE)
        {
            if (!tmp->next || tmp->next->type == PIPE)
                return (0);
        }
        tmp = tmp->next;
    }
    return (1);
}

bool    command_validation(t_first *uno)
{
    if (redirection_validation(uno) == 0)
        return (write(1, "syntax error\n", 13), 0);
    if (pipes_validation(uno) == 0)
        return (write(1, "syntax error\n", 13), 0);
    return (1);
}
