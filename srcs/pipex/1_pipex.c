/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:09:53 by kali              #+#    #+#             */
/*   Updated: 2023/07/08 10:05:50 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_args(t_tools tools)
{
	int	i;

	i = 0;
	if (tools.args)
	{
		while (tools.args[i])
		{
			free(tools.args[i]);
			i++;
		}
		free(tools.args);
	}
}

int	command_type(t_tools tools, t_cmd toc, char ***envp)
{
	tools.args = pipex_split(toc.commands[tools.i], " ");
	if (ft_strcmp(tools.args[0], "echo"))
	{
		tools.pid[tools.i] = fork();
		if (tools.pid[tools.i] == 0)
			ft_echo(tools, toc.commands[tools.i], toc, *envp);
		else
			g_exit_status = 0;
	}
	else if (is_builtin(tools.args[0], *envp))
	{
		if (builtin_exec(tools, toc, envp) == 1)
			return (free_args(tools), 1);
	}
	else
	{
		tools.pid[tools.i] = fork();
		if (tools.pid[tools.i] == 0)
			command_exec(tools, toc, *envp);
	}
	return (free_args(tools), 0);
}

int	pipex(t_cmd toc, char ***envp)
{
	t_tools	tools;

	ft_memset(&tools, 0, sizeof(tools));
	init_tools(&tools, toc);
	while (tools.i < toc.size)
	{
		if (toc.commands[tools.i] == NULL)
			;
		else if (command_type(tools, toc, envp) == 1)
		{
			clean_finish(tools, toc);
			free_all(tools);
			return (1);
		}
		(tools.i)++;
	}
	clean_finish(tools, toc);
	free_all(tools);
	return (0);
}

void	ft_pipe_manager(t_tools tools, t_cmd toc)
{
	int	j;

	j = 0;
	if (toc.inputs[tools.i] != -1)
		dup2(toc.inputs[tools.i], STDIN_FILENO);
	else if (tools.i > 0)
		dup2(tools.pipe_fd[tools.i - 1][0], STDIN_FILENO);
	if (toc.outputs[tools.i] != -1)
		dup2(toc.outputs[tools.i], STDOUT_FILENO);
	else if (tools.i < toc.size - 1)
		dup2(tools.pipe_fd[tools.i][1], STDOUT_FILENO);
	while (j < toc.size)
	{
		if (tools.pipe_fd[j][0] >= 0)
			close(tools.pipe_fd[j][0]);
		if (tools.pipe_fd[j][1] >= 0)
			close(tools.pipe_fd[j][1]);
		if (toc.inputs[j] >= 0)
			close(toc.inputs[j]);
		if (toc.outputs[j] >= 0)
			close(toc.outputs[j]);
		j++;
	}
}
