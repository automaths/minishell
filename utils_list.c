#include "execution.h"

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*list;

// 	if (*lst)
// 	{
// 		list = *lst;
// 		while (list->next)
// 			list = list->next;
// 		list->next = new;
// 	}
// 	else if (lst)
// 		*lst = new;
// }

// t_list	*ft_lstmap(t_list *lst)
// {
// 	t_list	*cpy;
// 	t_list	*new;

// 	new = NULL;
// 	if (!lst)
// 		return (NULL);
// 	while (lst)
// 	{
// 		cpy = ft_lstnew(lst->content);
// 		if (cpy == NULL)
// 			return (NULL);
// 		ft_lstadd_back(&new, cpy);
// 		lst = lst->next;
// 	}
// 	return (new);
// }

t_command	*new_command(int fd_in, int fd_out)
{
	t_command	*new;

	command = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// int	ft_lstsize(t_list *lst)
// {
// 	int		i;

// 	i = 0;
// 	while (lst)
// 	{
// 		i++;
// 		lst = lst->next;
// 	}
// 	return (i);
// }

// int	ft_lstcontent(t_list *lst, int index)
// {
// 	int	i;

// 	i = 0;
// 	while (lst != NULL && i < index - 1)
// 	{
// 		lst = lst->next;
// 		i++;
// 	}
// 	return (lst->content);
// }
