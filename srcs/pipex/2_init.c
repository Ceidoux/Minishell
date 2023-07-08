/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:39:35 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 09:24:57 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	init_tools(t_tools *tools, t_cmd_tab toc)
{
	tools->i = 0;
	tools->pipe_fd = malloc(sizeof(int *) * (toc.size + 1));
	if (tools->pipe_fd == NULL)
		return ;
	tools->pipe_fd[toc.size] = NULL;
	while (tools->i < toc.size)
	{
		tools->pipe_fd[tools->i] = malloc(sizeof(int) * 2);
		if (tools->pipe_fd[tools->i] == NULL)
		{
			free_before(tools);
			return ;
		}
		pipe(tools->pipe_fd[tools->i]);
		(tools->i)++;
	}
	tools->pid = malloc(sizeof(int) * toc.size);
	if (tools->pid == NULL)
		return ;
	tools->i = 0;
}
