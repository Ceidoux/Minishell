/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:39:40 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 13:54:43 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_option(char *str)
{
	if (str [0] && str[0] == '-')
	{
		if (str[1] && str[1] != '-')
		{
			error_pipex_printf("pwd: -%c: invalid option\n", str[1]);
			error_pipex_printf("pwd: usage: pwd [-LP]\n");
			return (1);
		}
		else if (str[1] && str[1] == '-'
			&& str[2])
		{
			error_pipex_printf("pwd: --: invalid option\n");
			error_pipex_printf("pwd: usage: pwd [-LP]\n");
			return (1);
		}
	}
	return (0);
}

void	pwd_invalid(t_tools tools, t_cmd toc, char **envp)
{
	if (tools.args[1])
	{
		if (invalid_option(tools.args[1]))
		{
			clean_finish(tools, toc);
			ft_tocfree(&toc);
			free_all(tools);
			ft_envp_free(envp);
			exit(2);
		}
	}
}

void	pwd_free(t_tools tools, t_cmd toc, char **envp)
{
	perror("pwd");
	clean_finish(tools, toc);
	ft_tocfree(&toc);
	free_all(tools);
	ft_envp_free(envp);
	exit(0);
}

int	ft_pwd(t_tools tools, t_cmd toc, char **envp)
{
	char	*current_dir;

	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
	{
		pwd_invalid(tools, toc, envp);
		ft_pipe_manager(tools, toc);
		current_dir = NULL;
		current_dir = getcwd(current_dir, 4096);
		if (!current_dir)
			pwd_free(tools, toc, envp);
		ft_putendl_fd(current_dir, 1);
		free(current_dir);
		clean_finish(tools, toc);
		ft_tocfree(&toc);
		free_all(tools);
		ft_envp_free(envp);
		exit(0);
	}
	return (0);
}
