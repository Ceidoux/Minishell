/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:39:40 by smestre           #+#    #+#             */
/*   Updated: 2023/07/05 18:28:42 by smestre          ###   ########.fr       */
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

int	ft_pwd(t_tools tools, t_cmd_tab toc)
{
	char	*current_dir;

	if (tools.args[1])
	{
		if (invalid_option(tools.args[1]))
			g_exit_status = 2;
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
			exit(1);
		}
		ft_putendl_fd(current_dir, 1);
		free(current_dir);
		exit(0);
	}
	return (0);
}
/*
A gérer (pas d'option)
[ok] pwd
[**] pwd qqc	-> print error: pwd: too many arguments
*/
