/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:33:48 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/08 14:34:52 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_last_cmd(t_cmd *toc);

/* add_new_line n'ajoute une ligne que si la dernier cmd n'est pas nulle*/
void	ft_add_new_line(t_cmd *toc)
{
	t_cmd	new_toc;
	int		line;

	if (!toc->size || ft_check_last_cmd(toc))
	{
		new_toc.size = toc->size + 1;
		new_toc.commands = calloc(new_toc.size, sizeof(*(new_toc.commands)));
		if (!(new_toc.commands))
			exit(EXIT_FAILURE);
		new_toc.inputs = calloc(new_toc.size, sizeof(*(new_toc.inputs)));
		new_toc.outputs = calloc(new_toc.size, sizeof(*(new_toc.outputs)));
		line = -1;
		while (++line < new_toc.size - 1)
		{
			if (toc->commands[line])
				new_toc.commands[line] = ft_strdup(toc->commands[line]);
			new_toc.inputs[line] = toc->inputs[line];
			new_toc.outputs[line] = toc->outputs[line];
		}
		new_toc.inputs[line] = -1;
		new_toc.outputs[line] = -1;
		ft_tocfree(toc);
		*toc = new_toc;
	}
}

/* ft_check_last_cmd returns 0 if last cmd is null */
static int	ft_check_last_cmd(t_cmd *toc)
{
	if (!toc->commands[toc->size - 1])
	{
		if (toc->inputs[toc->size - 1] != -1)
		{
			close(toc->inputs[toc->size - 1]);
			toc->inputs[toc->size - 1] = -1;
		}
		if (toc->outputs[toc->size - 1] != -1)
		{
			close(toc->outputs[toc->size - 1]);
			toc->outputs[toc->size - 1] = -1;
		}
		return (0);
	}
	return (1);
}
