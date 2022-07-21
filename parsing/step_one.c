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
        {
            write(1, "[APPEND] = ", 11);
            write(1, tmp->content, ft_strlen(tmp->content));
            write(1, "\n", 1);
        }
        if (tmp->type == WRITE)
        {
            write(1, "[WRITE] = ", 10);
            write(1, tmp->content, ft_strlen(tmp->content));
            write(1, "\n", 1);
        }
        if (tmp->type == HEREDOC)
        {
            write(1, "[HEREDOC] = ", 12);
            write(1, tmp->content, ft_strlen(tmp->content));
            write(1, "\n", 1);
        }
        if (tmp->type == READ)
        {
            write(1, "[READ] = ", 9);
            write(1, tmp->content, ft_strlen(tmp->content));
            write(1, "\n", 1);
        }
        if (tmp->type == PIPE)
        {
            write(1, "[PIPE] = ", 9);
            write(1, tmp->content, ft_strlen(tmp->content));
            write(1, "\n", 1);
        }
        if (tmp->type == WORD)
        {
            write(1, "[WORD] = ", 9);
            write(1, tmp->content, ft_strlen(tmp->content));
            write(1, "\n", 1);
        }
        if (tmp->type == BEGIN)
        {
            write(1, "[BEGIN] = ", 10);
            write(1, tmp->content, ft_strlen(tmp->content));
            write(1, "\n", 1);
        }
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
    int i;
    int j;
    t_first *uno;
    uno = new_uno(7, "start of chained list");
    i = -1;
    while (str[++i])
    {
        while (1)
        {
            if (str[i] == '>' && mode == NEUTRAL_MODE)
            {
                mode = R_REDIR_MODE;
                break;
            }

            if (mode == R_REDIR_MODE && str[i] == '>')
            {
                add_back_uno(&uno, new_uno(APPEND, alloc_content(&str[i - 1], 2)));
                mode = 0;
                break;
            }

            if (mode == R_REDIR_MODE && str[i] != '>')
            {
                add_back_uno(&uno, new_uno(WRITE, alloc_content(&str[i - 1], 1)));
                mode = actual_mode(str[i]);
            }

            if (str[i] == '<' && mode == NEUTRAL_MODE)
            {
                mode = L_REDIR_MODE;
                break;
            }

            if (mode == L_REDIR_MODE && str[i] == '<')
            {
                add_back_uno(&uno, new_uno(HEREDOC, alloc_content(&str[i - 1], 2)));
                mode = 0;
                break;
            }
            
            if (mode == L_REDIR_MODE&& str[i] != '<')
            {
                add_back_uno(&uno, new_uno(READ, alloc_content(&str[i - 1], 1)));
                mode = actual_mode(str[i]);
            }
            
            if (str[i] == '|')
            {
                add_back_uno(&uno, new_uno(PIPE, alloc_content(&str[i], 1)));
                break;
            }
            
            if (str[i] == ' ')
                break;
            
            if (str[i] == '"')
                mode = DQUOTE_MODE;
            
            else if (str[i] == '\'')
                mode = SQUOTE_MODE;
            
            else
                mode = WORD_MODE;
            
            j = 0;
            while (str[i + ++j] && (mode == 3 || mode == 4 || mode == 5))
            {
                if ((actual_mode(str[i + j]) != WORD_MODE) && (mode == WORD_MODE))
                {
                    mode = NEUTRAL_MODE;
                    break;
                }
                if (str[i + j] == '"' && mode == DQUOTE_MODE)
                {
                    mode = WORD_MODE;
                    if (actual_mode(str[i + j + 1]) != WORD_MODE)
                    {
                        mode = NEUTRAL_MODE;
                        break;
                    }
                }
                if (str[i + j] == '\'' && mode == SQUOTE_MODE)
                {
                    mode = WORD_MODE;
                    if (actual_mode(str[i + j + 1]) != WORD_MODE)
                    {
                        mode = NEUTRAL_MODE;
                        break;
                    }
                }
            }
            add_back_uno(&uno, new_uno(WORD, alloc_content(&str[i], j + 1)));
            i += j;
            break;
        }
    }
    if (mode == DQUOTE_MODE)
        return (write(1, "Error, double quotes not ended\n", 31), NULL);
        if (mode == SQUOTE_MODE)
        return (write(1, "Error, single quotes not ended\n", 31), NULL);
    return (uno);
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