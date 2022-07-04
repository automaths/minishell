#include "execution.h"

t_env	*new_lst(char *name, char *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	add_back_lst(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (lst)
		*lst = new;
}

int	strnstr_int(char *str, char *to_find)
{
	int	i;
	int	j;

	if (to_find[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}
