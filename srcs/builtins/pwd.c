/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:37:44 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/02 17:38:27 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_option(char *str)
{
	int	i;
	int	change_fd;

	change_fd = dup(STDOUT_FILENO);
	i = 0;
	dup2(STDOUT_FILENO, STDERR_FILENO);
	if (str [0] && str[0] == '-')
	{
		if (str[1] && str[1] != '-')
		{
			pipex_printf("pwd: -%c: invalid option\n", str[1]);
			pipex_printf("pwd: usage: pwd [-LP]\n");
			dup2(STDOUT_FILENO, change_fd);
			close(change_fd);
			return (1);
		}
		else if (str[1] && str[1] == '-'
			&& str[2])
		{
			pipex_printf("pwd: --: invalid option\n");
			pipex_printf("pwd: usage: pwd [-LP]\n");
			dup2(STDOUT_FILENO, change_fd);
			close(change_fd);
			return (1);
		}
	}
	dup2(STDOUT_FILENO, change_fd);
	close(change_fd);
	return (0);
}

int	ft_pwd(t_tools tools)
{
	char	*current_dir;

	if (tools.args[1])
	{
		if (invalid_option(tools.args[1]))
		{
			g_exit_status = 2;
			return (0);
		}
	}
	current_dir = NULL;
	current_dir = getcwd(current_dir, 4096);
	if (!current_dir)
	{
		perror("pwd");
		return (1);
	}
	ft_putendl_fd(current_dir, 1);
	free(current_dir);
	return (0);
}

/*
A gérer (pas d'option)
[ok] pwd
[**] pwd qqc	-> print error: pwd: too many arguments
*/
