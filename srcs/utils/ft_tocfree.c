/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tocfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:05:57 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/01 17:06:24 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tocfree(t_table_of_commands *toc)
{
	int	line;

	line = toc->size;
	while (--line >= 0)
	{
		free(toc->commands[line]);
		toc->commands[line] = NULL;
	}
	if (toc->size)
	{
		free(toc->inputs);
		toc->inputs = NULL;
		free(toc->outputs);
		toc->outputs = NULL;
	}	
	toc->size = 0;
}

