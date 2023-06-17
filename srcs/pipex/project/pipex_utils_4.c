/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:51:05 by smestre           #+#    #+#             */
/*   Updated: 2023/06/16 17:41:32 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	absolute_relative_path(t_tools tools)
{
	tools.str = ft_strdup(tools.args[0]);
	if (tools.str == NULL)
		return ;
	if (access(tools.str, F_OK) == -1)
	{
		perror(tools.str);
		free_str_args(tools);
		exit(0);
	}
	else if (access(tools.str, X_OK) == -1)
	{
		perror(tools.str);
		free_str_args(tools);
		exit(0);
	}
	else if (end_slash(tools.str))
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		ft_printf("%s: Is a directory\n", tools.str);
		free_str_args(tools);
		exit(0);
	}
	tools.args[0] = remove_path(tools.args[0]);
	execve(tools.str, tools.args, NULL);
}

void	no_path(t_tools tools)
{
	dup2(tools.saved_std_out, 1);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("Command not found : %s \n", tools.args[0]);
	free_no_path(tools);
	exit(0);
}

void	env_path(t_tools tools, char **envp)
{
	tools.str = path_line(envp);
	if (tools.str == NULL)
		no_path(tools);
	tools.paths = ft_split_slash(tools.str, ':');
	while (tools.paths && tools.paths[tools.i])
	{
		tools.paths[tools.i] = ft_strjoin(tools.paths[(tools.i)],
				tools.args[0]);
		if (tools.paths[tools.i] == NULL)
			return ;
		execve(tools.paths[tools.i], tools.args, NULL);
		(tools.i)++;
	}
	no_execution(tools);
}

void	no_execution(t_tools tools)
{
	dup2(tools.saved_std_out, 1);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("Command not found : %s \n", tools.args[0]);
	free_all(tools);
	exit(0);
}

void	print_error(t_tools tools, char *str)
{
	perror(str);
	free_all(tools);
	exit(0);
}
