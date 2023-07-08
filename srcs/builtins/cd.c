/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:14 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 11:32:43 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_many_arguments(t_tools tools, t_cmd toc)
{
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
	{
		ft_pipe_manager(tools, toc);
		error_pipex_printf("cd: too many arguments\n");
		ft_tocfree(&toc);
		free_main(&tools);
		free_all(tools);
		exit(1);
	}
}

void	cd_no_home(t_tools tools, t_cmd toc)
{
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
	{
		ft_pipe_manager(tools, toc);
		error_pipex_printf("cd: HOME not set\n");
		ft_tocfree(&toc);
		free_main(&tools);
		free_all(tools);
		exit(1);
	}
}

void	cd_no_directory(t_tools tools, t_cmd toc, char *str, char **envp)
{
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
	{
		ft_pipe_manager(tools, toc);
		perror(str);
		ft_tocfree(&toc);
		ft_envp_free(envp);
		free_main(&tools);
		free_all(tools);
		exit(1);
	}
}

void	cd_not_exist(t_tools tools, t_cmd toc, char **envp)
{
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
	{
		ft_pipe_manager(tools, toc);
		perror(tools.args[1]);
		ft_tocfree(&toc);
		ft_envp_free(envp);
		free_main(&tools);
		free_all(tools);
		exit(1);
	}
}

int	ft_cd(t_tools tools, char **envp, t_cmd toc)
{
	char	*str;

	if (arg_size(tools) > 2)
		return (cd_many_arguments(tools, toc), 0);
	if (arg_size(tools) == 1 || (arg_size(tools) == 2
			&& ft_strcmp(tools.args[1], "~")))
	{
		str = ft_getenv("HOME", envp);
		if (str == NULL)
			return (cd_no_home(tools, toc), 0);
		if (chdir(str) == -1)
			return (cd_no_directory(tools, toc, str, envp), 0);
	}
	else if (arg_size(tools) == 2)
	{
		if (chdir(tools.args[1]) == -1)
			return (cd_not_exist(tools, toc, envp), 0);
	}
	g_exit_status = 0;
	return (0);
}
