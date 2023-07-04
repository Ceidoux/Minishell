/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_close_free_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:44:03 by kali              #+#    #+#             */
/*   Updated: 2023/07/04 14:27:28 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	clean_finish(t_tools tools, t_cmd_tab toc)
{
	tools.i = 0;
	while (tools.i < toc.size)
	{
		if (tools.pipe_fd[tools.i][0] >= 0)
			close(tools.pipe_fd[tools.i][0]);
		if (tools.pipe_fd[tools.i][1] >= 0)
			close(tools.pipe_fd[tools.i][1]);
		if (toc.inputs[tools.i] >= 0)
			close(toc.inputs[tools.i]);
		if (toc.outputs[tools.i] >= 0)
			close(toc.outputs[tools.i]);
		(tools.i)++;
	}
	while (toc.size > 0)
	{
		wait(NULL);
		(toc.size)--;
	}
	free_main(&tools);
}

void	no_execution(t_tools tools)
{
	// perror(tools.args[0]);
	error_pipex_printf("%s: command not found\n", tools.args[0]);
	free_all(tools);
	free_main(&tools);
	exit(127);
}

void	free_no_path(t_tools tools)
{
	int	i;

	i = 0;
	while (tools.args[i])
		free(tools.args[i++]);
	free(tools.args);
}

void	failed_open(t_tools tools, char **argv)
{
	int	i;

	i = 0;
	perror(argv[1]);
	close(tools.pipe_fd[0][1]);
	close(tools.pipe_fd[0][0]);
	while (tools.args[i])
		free(tools.args[i++]);
	free(tools.args);
	free_main(&tools);
	exit(0);
}

void	close_pipes(t_tools tools, t_cmd_tab toc)
{
	int	j;

	j = 0;
	while (j < toc.size)
	{

		close(tools.pipe_fd[j][0]);
		close(tools.pipe_fd[j][1]);
		close(toc.inputs[j]);
		close(toc.outputs[j]);
		j++;
	}
}
