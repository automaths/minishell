#include "../execution.h"

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

char *alloc_content(char *str, unsigned int size)
{
    char *alloc;
    unsigned int i;

    alloc = (char *)malloc(sizeof(char) * (size + 1));
    if (alloc == NULL)
        return (NULL);
    alloc[size] = '\0';
    i = -1;
    while (str[++i] && i < size)
        alloc[i] = str[i];
    return (alloc);
}

void print_step_one(t_first *uno)
{
    t_first *tmp;
    tmp = uno;
    while (tmp != NULL)
    {
        if (tmp->type == APPEND)
            printf("[%s] = %s\n", "APPEND", tmp->content);
        if (tmp->type == WRITE)
            printf("[%s] = %s\n", "WRITE", tmp->content);
        if (tmp->type == HEREDOC)
            printf("[%s] = %s\n", "HEREDOC", tmp->content);
        if (tmp->type == READ)
            printf("[%s] = %s\n", "READ", tmp->content);
        if (tmp->type == PIPE)
            printf("[%s] = %s\n", "PIPE", tmp->content);
        if (tmp->type == WORD)
            printf("[%s] = %s\n", "WORD", tmp->content);
        if (tmp->type == BEGIN)
            printf("[%s] = %s\n", "BEGIN", tmp->content);
        tmp = tmp->next;
    }
}

t_first	*new_uno(int type, char *content)
{
	t_first	*new;

	new = (t_first *)malloc(sizeof(t_first));
	if (new == NULL)
		return (NULL);
    new->type = type;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	add_back_uno(t_first **uno, t_first *new)
{
	t_first	*tmp;

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

t_first *step_one(char *str)
{
    unsigned int mode = NEUTRAL_MODE;
    t_first *uno;
    uno = new_uno(7, "start of chained list");
    unsigned int i = -1;
    while (str[++i])
    {
        while (1)
        {
            if (str[i] == '>' && mode == NEUTRAL_MODE)
            {
                mode = R_REDIR_MODE;
                break;
            }
            if (mode == R_REDIR_MODE)
            {
                if (str[i] == '>')
                {
                    add_back_uno(&uno, new_uno(APPEND, alloc_content(str[i - 1], 2)));
                    mode = 0;
                    break;
                }
                else
                {
                    add_back_uno(&uno, new_uno(WRITE, alloc_content(str[i - 1], 1)));
                    mode = actual_mode(str[i]); //if pipe action need to be taken adequately
                    break;
                }
            }
            if (str[i] == '<' && mode == NEUTRAL_MODE)
            {
                mode = L_REDIR_MODE;
                break;
            }
            if (mode == L_REDIR_MODE)
            {
                if (str[i] == '<')
                {
                    add_back_uno(&uno, new_uno(HEREDOC, alloc_content(str[i - 1], 2)));
                    mode = 0;
                    break;
                }
                else
                {
                    add_back_uno(&uno, new_uno(READ, alloc_content(str[i - 1], 1)));
                    mode = actual_mode(str[i]); //if pipe action need to be taken adequately
                    break;
                }
            }
            
        }
    }
}


/*
mode 0:
    if > mode 1
        if > append
        else write
    if < mode 2
        if < heredoc
        else read
    if | pipe 
    if alphanumeric mode 3
        if alphanumeric mode 3
        if ' mode 4 
        if " mode 5
        if space < > | word mode 0
    if ' mode 4
        if ' mode 3
        if " mode 5
    if " mode 5
        if " mode 3
        if ' mode 4
*/