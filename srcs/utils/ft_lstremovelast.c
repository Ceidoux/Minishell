# include "minishell.h"

void	ft_lstremovelast(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	while (lst->next->next)
		lst = lst->next;
	(*del)(lst->next->content);
	free(lst->next);
	lst->next = NULL;
}
