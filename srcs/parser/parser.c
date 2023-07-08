/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:00:48 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/08 14:35:38 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	ft_remove_last_line(t_cmd *toc);

t_cmd	ft_parser(char *s, char **envp)
{
	t_cmd	toc;
	t_list	*tokens;

	tokens = ft_lexer(s, envp);
	toc = ft_create_table_of_commands(tokens, envp);
	ft_lstclear(&tokens, &free);
	if (toc.size && !toc.commands[toc.size - 1])
		toc = ft_remove_last_line(&toc);
	return (toc);
}

/* remove last line if cmd is null */
static t_cmd	ft_remove_last_line(t_cmd *toc)
{
	t_cmd	new_toc;
	int		idx;

	new_toc.size = toc->size - 1;
	idx = -1;
	while (++idx < new_toc.size)
	{
		new_toc.commands = malloc(new_toc.size * sizeof(char *));
		new_toc.commands[idx] = ft_strdup(toc->commands[idx]);
		new_toc.inputs = malloc(new_toc.size * sizeof(int));
		new_toc.inputs[idx] = toc->inputs[idx];
		new_toc.outputs = malloc(new_toc.size * sizeof(int));
		new_toc.outputs[idx] = toc->outputs[idx];
	}
	if (toc->inputs[toc->size - 1] != -1)
		close(toc->inputs[toc->size - 1]);
	if (toc->outputs[toc->size - 1] != -1)
		close(toc->outputs[toc->size - 1]);
	ft_tocfree(toc);
	return (new_toc);
}
