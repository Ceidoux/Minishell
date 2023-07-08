/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:00:23 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 14:01:55 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	export_free_1(t_tools tools, t_cmd toc, char **envp)
{
	ft_tocfree(&toc);
	ft_envp_free(envp);
	free_main(&tools);
	free_all(tools);
	exit(0);
}

void	export_free_2(t_tools tools, t_cmd toc, char **envp)
{
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
	{
		ft_pipe_manager(tools, toc);
		ft_tocfree(&toc);
		ft_envp_free(envp);
		free_main(&tools);
		free_all(tools);
		exit(0);
	}
}

void	export_not_valid(t_tools *tools, t_cmd toc, char ***envp, int *i)
{
	tools->status_flag = 1;
	tools->pid[tools->i] = fork();
	if (tools->pid[tools->i] == 0)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(tools->args[*i + 1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		ft_pipe_manager(*tools, toc);
		ft_tocfree(&toc);
		ft_envp_free(*envp);
		free_main(tools);
		free_all(*tools);
		exit(1);
	}
}
