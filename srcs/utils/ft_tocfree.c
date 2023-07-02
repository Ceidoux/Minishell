/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tocfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:05:57 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/02 17:04:29 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tocfree(t_cmd_tab *toc)
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
		free(toc->commands);
		toc->commands = NULL;
		free(toc->inputs);
		toc->inputs = NULL;
		free(toc->outputs);
		toc->outputs = NULL;
	}	
	toc->size = 0;
}
