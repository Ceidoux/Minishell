/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:39:35 by smestre           #+#    #+#             */
/*   Updated: 2023/06/22 21:19:43 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


/*

Fonction d'initialisation des tools pour pipex. 

*/

void	init_tools(t_tools *tools, t_table_of_commands toc)
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




