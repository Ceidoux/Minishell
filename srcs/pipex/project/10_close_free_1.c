/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_close_free_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:39:32 by kali              #+#    #+#             */
/*   Updated: 2023/06/23 10:19:48 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

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
	free(tools->pid);
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
	while (tools.paths[i])
		free(tools.paths[i++]);
	free(tools.paths);
	i = 0;
	while (tools.args[i])
		free(tools.args[i++]);
	free(tools.args);
}