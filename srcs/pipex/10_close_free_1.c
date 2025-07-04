/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_close_free_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:39:32 by kali              #+#    #+#             */
/*   Updated: 2023/07/08 14:29:16 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_str_args(t_tools tools)
{
	int	i;

	i = 0;
	while (tools.args[i])
	{
		free(tools.args[i]);
		i++;
	}
	free(tools.args);
	free(tools.str);
}

void	free_main(t_tools *tools)
{
	tools->i = 0;
	while (tools->pipe_fd[tools->i])
	{
		free(tools->pipe_fd[tools->i]);
		(tools->i)++;
	}
	free(tools->pipe_fd);
	tools->pipe_fd = NULL;
	free(tools->pid);
	tools->pid = NULL;
}

void	free_path(t_tools tools)
{
	perror(tools.str);
	free_str_args(tools);
	free_main(&tools);
	exit(0);
}

void	free_before(t_tools *tools)
{
	int	i;

	i = 0;
	while (i < tools->i)
		free(tools->pipe_fd[i++]);
	free(tools->pipe_fd);
}

void	free_all(t_tools tools)
{
	int	i;

	i = 0;
	free(tools.str);
	if (tools.paths)
	{
		while (tools.paths[i])
			free(tools.paths[i++]);
		free(tools.paths);
		tools.paths = NULL;
	}
	i = 0;
	if (tools.args)
	{
		while (tools.args[i])
			free(tools.args[i++]);
		free(tools.args);
		tools.args = NULL;
	}
}
