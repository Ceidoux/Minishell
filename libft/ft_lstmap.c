/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:02:31 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/14 12:54:42 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*penultimate;
	t_list	*last;

	first = NULL;
	penultimate = NULL;
	while (lst)
	{
		last = malloc(sizeof(*last));
		if (!last)
			return (ft_lstclear(&first, del), NULL);
		if (!first)
			first = last;
		else
			penultimate->next = last;
		penultimate = last;
		last->content = (*f)(lst->content);
		last->next = NULL;
		lst = lst->next;
	}
	return (first);
}
