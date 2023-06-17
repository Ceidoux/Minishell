/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:09:53 by kali              #+#    #+#             */
/*   Updated: 2023/06/16 16:09:26 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_command(t_tools tools, char **argv, char **envp)
{
	tools.saved_std_out = dup(1);
	tools.i = 0;
	tools.file_fd = open(argv[1], O_RDONLY, 0644);
	if (tools.file_fd == -1)
	{
		perror(argv[1]);
		close(tools.pipe_fd[0]);
		close (tools.pipe_fd[1]);
		close(tools.saved_std_out);
		exit(0);
	}
	dup2(tools.file_fd, STDIN_FILENO);
	close(tools.file_fd);
	tools.args = ft_split(argv[2], ' ');
	close(tools.pipe_fd[0]);
	dup2(tools.pipe_fd[1], STDOUT_FILENO);
	close(tools.pipe_fd[1]);
	close(tools.saved_std_out);
	if (is_slash(tools.args[0]))
		absolute_relative_path(tools);
	else
		env_path(tools, envp);
}

void	second_command(t_tools tools, char **argv, char **envp)
{
	tools.saved_std_out = dup(1);
	tools.i = 0;
	tools.file_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (tools.file_fd == -1)
	{
		perror(argv[4]);
		close(tools.pipe_fd[0]);
		close (tools.pipe_fd[1]);
		close(tools.saved_std_out);
		exit(0);
	}
	dup2(tools.pipe_fd[0], STDIN_FILENO);
	close(tools.pipe_fd[0]);
	close (tools.pipe_fd[1]);
	dup2(tools.file_fd, STDOUT_FILENO);
	close(tools.file_fd);
	close(tools.saved_std_out);
	tools.args = ft_split(argv[3], ' ');
	if (is_slash(tools.args[0]))
		absolute_relative_path(tools);
	else
		env_path(tools, envp);
}

int	main(int argc, char *argv[], char **envp)
{
	t_tools	tools;

	if (argc != 5)
		return (syntax_help());
	if (non_printable(argv[2]) || non_printable(argv[3]))
		return (syntax_help());
	pipe(tools.pipe_fd);
	tools.pid[0] = fork();
	if (tools.pid[0] == 0)
		first_command(tools, argv, envp);
	tools.pid[1] = fork();
	if (tools.pid[1] == 0)
		second_command(tools, argv, envp);
	close(tools.pipe_fd[0]);
	close(tools.pipe_fd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
