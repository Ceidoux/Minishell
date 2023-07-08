/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremovelast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:04:41 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/08 10:12:07 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstremovelast(t_list **lst, void (*del)(void*))
{
	if (!lst || !(*lst))
		return ;
	if (!(*lst)->next)
	{
		(*del)((*lst)->content);
		free(*lst);
		*lst = NULL;
		return ;
	}
	while ((*lst)->next->next)
		lst = &((*lst)->next);
	(*del)((*lst)->next->content);
	free((*lst)->next);
	(*lst)->next = NULL;
}
