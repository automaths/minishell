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

int	opening_append(char *content)
{
	int fd;

	content = ft_strtrim(content, "> ");
	if (access(content, F_OK) == 0)
	{
		if (access(content, W_OK) == -1)
			return (writing("can't write the file", " "), -1);
	}
	fd = open(content, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return (writing("cant open file", " "), -1);
	return (fd);
}

int	opening_standard_output(char *content)
{
	int fd;

	content = ft_strtrim(content, "> ");
	if (access(content, F_OK) == 0)
	{
		if (access(content, W_OK) == -1)
			return (writing("can't write the file", " "), -1);
	}
	fd = open(content, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return (writing("cant open file", " "), -1);
	return (fd);
}

int	opening_heredoc(char *content)
{
	int fd;
	(void)content;
	fd = open("tmp_file", O_RDWR);
	return (fd);
}

int	opening_standard_input(char *content)
{
	int fd;

	content = ft_strtrim(content, "< ");
	if (access(content, F_OK) == 0)
	{
		if (access(content, R_OK) == -1)
			return (writing("can't read the file", " "), -1);
	}
	fd = open(content, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return (writing("can't open the file", " "), -1);
	return (fd);
}
