/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:39:40 by smestre           #+#    #+#             */
/*   Updated: 2023/07/06 16:17:23 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_invalid(char *str)
// {
// 	if (str [0] && str[0] == '-')
// 	{
// 		if (str[1] && str[1] != '-')
// 			return (1);
// 		else if (str[1] && str[1] == '-'
// 			&& str[2])
// 			return (1);
// 	}
// 	return (0);
// }

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

int	ft_pwd(t_tools tools, t_cmd_tab toc, char **envp)
{
	char	*current_dir;

	if (tools.args[1])
	{
		if (invalid_option(tools.args[1]))
			return (g_exit_status = 2, 0);
		else
			g_exit_status = 0;
	}
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
	{
		ft_pipe_manager(tools, toc);
		current_dir = NULL;
		current_dir = getcwd(current_dir, 4096);
		if (!current_dir)
		{
			perror("pwd");
			clean_finish(tools, toc);
			ft_tocfree(&toc);
			free_all(tools);
			ft_envp_free(envp);
			exit(0);
		}
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
/*
A gérer (pas d'option)
[ok] pwd
[**] pwd qqc	-> print error: pwd: too many arguments
*/
