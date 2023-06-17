/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_5_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:06:34 by smestre           #+#    #+#             */
/*   Updated: 2023/06/16 17:03:15 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	failed_open(t_tools tools, char **argv)
{
	int	i;

	i = 0;
	perror(argv[1]);
	close(tools.pipe_fd[0][1]);
	close(tools.pipe_fd[0][0]);
	close(tools.saved_std_out);
	while (tools.args[i])
		free(tools.args[i++]);
	free(tools.args);
	free_main(&tools);
	exit(0);
}

void	close_rest_1(t_tools tools, int first_fd)
{
	close(tools.pipe_fd[0][1]);
	close(tools.pipe_fd[0][0]);
	close(first_fd);
	close(tools.saved_std_out);
}

void	first_part(t_tools tools, int argc, char **argv, char **envp)
{
	tools.pid[0] = fork();
	if (tools.pid[0] == 0)
	{	
		if (non_printable(argv[2]))
		{
			syntax_help();
			free_main(&tools);
			exit(0);
		}
		first_command(tools, argc, argv, envp);
	}
}

void	last_part(t_tools tools, char **argv, char **envp)
{
	tools.pid[tools.i - 2] = fork();
	if (tools.pid[tools.i - 2] == 0)
	{
		if (non_printable(argv[tools.i]))
		{
			syntax_help();
			free_main(&tools);
			exit(0);
		}		
		last_command(tools, argv[tools.i], argv[tools.i + 1], envp);
	}
}

void	free_no_path(t_tools tools)
{
	int	i;

	i = 0;
	while (tools.args[i])
		free(tools.args[i++]);
	free(tools.args);
}
