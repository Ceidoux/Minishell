/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:04:35 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/01 17:06:34 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
