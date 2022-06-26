#include "execution.h"

// <<a : 
// 		heredoc link avec le fichier temporaire
// <a : 
// 		si mauvais chmod ou existe pas erreur traite aucune commande 
// 		si a la suite le dernier est ouvert
// >a : 
// 		cree un fichier chmod 644 si existe pas 
// 		si mauvais chmod erreur traite aucune commande
// 		si elle se suive seulement derniere
// >>a : 
// 		comme >a mais en mode append

bool	is_heredoc(char *str)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '<')
			++j;	
	}
	if (j == 2)
		return (1);
	return (0);
}

bool	is_append(char *str)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '>')
			++j;	
	}
	if (j == 2)
		return (1);
	return (0);
}

void	init_fd_in(t_command *cmd)
{
	t_token *tmp;
	char *content;
	
	tmp = cmd->redir;
	content = NULL;
	while (tmp != NULL)
	{
		if (is_redirection(tmp->content) == 1)
			content = tmp->content;
		tmp = tmp->next;
	}
	if (content != NULL)
	{
		if (is_heredoc(content))
			cmd->fd_in = opening_heredoc(content);
		if (!is_heredoc(content))
			cmd->fd_in = opening_standard_input(content);
	}
}

void	init_fd_out(t_command *cmd)
{
	t_token *tmp;
	char *content;
	
	tmp = cmd->redir;
	content = NULL;
	while (tmp != NULL)
	{
		if (is_redirection(tmp->content) == 2)
			content = tmp->content;
		tmp = tmp->next;
	}
	if (content != NULL)
	{
		if (is_append(content))
			cmd->fd_out = opening_append(content);
		if (!is_append(content))
			cmd->fd_out = opening_standard_output(content);
	}
}

void	redirectionning(t_command *cmd)
{
	init_fd_in(cmd);
	init_fd_out(cmd);
}
