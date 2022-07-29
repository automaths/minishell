#include "../../execution.h"

int actual_mode(char c)
{
    if (c == '>')
        return (R_REDIR_MODE);
    if (c == '<')
        return (L_REDIR_MODE);
    if (c == '|')
        return (PIPE);
    if (c == '\"')
        return (DQUOTE_MODE);
    if (c == '\'')
        return (SQUOTE_MODE);
    if (c == ' ')
        return (NEUTRAL_MODE);
    else
        return (WORD_MODE);
}

char    *alloc_content(char *str, unsigned int size)
{
    char            *alloc;
    unsigned int    i;

    alloc = (char *)malloc(sizeof(char) * (size + 1));
    if (alloc == NULL)
        return (NULL);
    alloc[size] = '\0';
    i = -1;
    while (str[++i] && i < size)
        alloc[i] = str[i];
    return (alloc);
}

t_first *new_uno(int type, char *content)
{
	t_first *new;

	new = (t_first *)malloc(sizeof(t_first));
	if (new == NULL)
		return (NULL);
    new->type = type;
	new->content = content;
	new->next = NULL;
	return (new);
}

void    add_back_uno(t_first **uno, t_first *new)
{
	t_first *tmp;

	if (*uno)
	{
		tmp = *uno;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (uno)
		*uno = new;
}
