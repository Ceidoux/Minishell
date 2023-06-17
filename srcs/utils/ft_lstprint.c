#include "minishell.h"

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		if (lst->type)
			ft_putstr_fd("WORD:", 1);
		else
			ft_putstr_fd("OPERATOR:", 1);
		ft_putendl_fd(lst->content, 1);
		lst = lst->next;
	}
}
