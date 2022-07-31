# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "errno.h"

typedef struct s_garbage
{
	char **d_char;
	char *s_char;
	struct s_garbage *next;
}	t_garbage;

typedef struct s_command
{
	t_garbage	*garbage;
	struct s_command	*next;
}	t_command;

void	updator_next(t_command *cmd)
{
	t_command *tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		tmp->garbage = cmd->garbage;
		tmp = tmp->next;
	}
}

void	updator_all(t_command *cmd)
{
	t_command *tmp;
	t_command *tnp;

	tmp = cmd;
	while(tmp->next != NULL)
		tmp = tmp->next;
	tnp = cmd;
	while (tnp != NULL)
	{
		tnp->garbage = tmp->garbage;
		tnp = tnp->next;
	}
}

t_garbage	*new_garbage(char **d_char, char *s_char)
{
	t_garbage	*new;

	new = (t_garbage *)malloc(sizeof(t_garbage));
	if (new == NULL)
		return (NULL);
	new->d_char = d_char;
	new->s_char = s_char;
	new->next = NULL;
	return (new);
}

void	add_garbage(t_garbage **grb, t_garbage *new)
{
	t_garbage	*tmp;

	if (*grb)
	{
		tmp = *grb;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (grb)
		*grb = new;
}

void	clean_garbage(t_garbage **grb)
{
	t_garbage	*tmp;
	t_garbage	*next;
	int			i;

	tmp = *grb;
	while (tmp)
	{
		next = tmp->next;
		if ((*grb)->d_char != NULL)
		{
			i = -1;
			while ((*grb)->d_char[++i] != NULL)
			{
				free((*grb)->d_char[i]);
			}
			free((*grb)->d_char);
		}
		if ((*grb)->s_char != NULL)
			free((*grb)->s_char);
		free(tmp);
		tmp = next;
	}
	*grb = NULL;
}

int	main(void)
{
	char **split;
	char *hola;
	char **hello;
	char *halo;
	int i;

	split = (char **)malloc(sizeof(char *) * 2);
	split[0] = strdup("yoyo");
	split[1] = strdup("heyhey");
	hello = (char **)malloc(sizeof(char *) * 2);
	hello[0] = strdup("yoyo");
	hello[1] = strdup("heyhey");
	hola = strdup("cavamec");
	halo = strdup("ouaiouai");

	i = -1;
	while (split[++i] != NULL)
	{
		free(split[i]);
	}
	free(split);
	i = -1;
	while (hello[++i] != NULL)
	{
		free(hello[i]);
	}
	free(hello);
	free(hola);
	free(halo);
	return (0);
}