#include "../execution.h"

int    lexer_id_one(char c, int *mode)
{
    if (c == ' ' || c == ';')
        return (0);
    if (c == '>' && *mode == NEUTRAL_MODE)
    {
        *mode = R_REDIR_MODE;
        return (0);
    }
    if (c == '<' && *mode == NEUTRAL_MODE)
    {
        *mode = L_REDIR_MODE;
        return (0);
    }
    return (1);        
}

int     lexer_id_two(t_first **uno, char *str, int *mode)
{
    int i;
    i = 1;
    if (*mode == R_REDIR_MODE && str[i] == '>')
    {
        add_back_uno(uno, new_uno(APPEND, alloc_content(&str[i - 1], 2)));
        *mode = NEUTRAL_MODE;
        return (0);
    }
    if (*mode == R_REDIR_MODE && str[i] != '>')
    {
        add_back_uno(uno, new_uno(WRITE, alloc_content(&str[i - 1], 1)));
        *mode = actual_mode(str[i]);
    }
    if (*mode == L_REDIR_MODE && str[i] == '<')
    {
        add_back_uno(uno, new_uno(HEREDOC, alloc_content(&str[i - 1], 2)));
        *mode = NEUTRAL_MODE;
        return (0);
    }
    if (*mode == L_REDIR_MODE&& str[i] != '<')
    {
        add_back_uno(uno, new_uno(READ, alloc_content(&str[i - 1], 1)));
        *mode = actual_mode(str[i]);
    }
    if (str[i] == '|')
    {
        add_back_uno(uno, new_uno(PIPE, alloc_content(&str[i], 1)));
        return (0);
    }
    return (1);
}

void     lexer_id_three(t_first **uno, char *str, int *mode, int *i)
{
    int j;

    if (str[*i] == '"')
        *mode = DQUOTE_MODE;
    
    else if (str[*i] == '\'')
        *mode = SQUOTE_MODE;
    
    else
        *mode = WORD_MODE;
    
    j = 0;
    while (str[*i + ++j] && (*mode == 3 || *mode == 4 || *mode == 5))
    {
        if ((actual_mode(str[*i + j]) != WORD_MODE) && (*mode == WORD_MODE))
        {
            *mode = NEUTRAL_MODE;
            break;
        }
        if (str[*i + j] == '"' && *mode == DQUOTE_MODE)
        {
            j++;
            *mode = NEUTRAL_MODE;
            break;
        }
        if (str[*i + j] == '\'' && *mode == SQUOTE_MODE)
        {
            j++;
            *mode = NEUTRAL_MODE;
            break;
        }
        if (!str[*i + j + 1])
        {
            *mode = NEUTRAL_MODE;
            break;
        }
    }
    if (*mode != WORD_MODE)
        add_back_uno(uno, new_uno(WORD, alloc_content(&str[*i], j)));
    *i = *i + j - 1;
}

bool check_quotes(char *str)
{
    int i;
    int mode;

    i = -1;
    mode = 0;
    while (str[++i])
    {
        while (1)
        {
            if (str[i] == '"' && mode == NEUTRAL_MODE)
            {
                mode = DQUOTE_MODE;
                break;
            }
            if (str[i] == '"' && mode == DQUOTE_MODE)
            {
                mode = NEUTRAL_MODE;
                break;
            }
            if (str[i] == '\'' && mode == NEUTRAL_MODE)
            {
                mode = SQUOTE_MODE;
                break;
            }
            if (str[i] == '\'' && mode == SQUOTE_MODE)
            {
                mode = NEUTRAL_MODE;
                break;
            }
            break;
        }
    }
    if (mode == SQUOTE_MODE || mode == DQUOTE_MODE)
        return (0);
    return (1);
}

t_first *step_one(char *str)
{
    t_first *uno;
    int mode;
    int i;

    if (check_quotes(str) == 0)
        return (write(1, "Error, double quotes not ended\n", 31), NULL);

    mode = NEUTRAL_MODE;
    uno = new_uno(7, "start of chained list");
    i = -1;
    while (str[++i])
    {
        while (1)
        {
            if (lexer_id_one(str[i], &mode) == 0)
                break;
            if (lexer_id_two(&uno, &str[i - 1], &mode) == 0)
                break;
            lexer_id_three(&uno, str, &mode, &i);
            break;
        }
    }
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