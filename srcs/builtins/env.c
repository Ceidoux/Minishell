/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:34 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 14:05:24 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_has_equal_sign(char *s);

int	ft_env(t_tools tools, t_cmd toc, char **envp)
{
	int	i;

	i = 0;
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
	{
		ft_pipe_manager(tools, toc);
		while (envp[i])
		{
			if (ft_has_equal_sign(envp[i]))
				ft_putendl_fd(envp[i], 1);
			i++;
		}
		clean_finish(tools, toc);
		ft_tocfree(&toc);
		free_all(tools);
		ft_envp_free(envp);
		exit(0);
	}
	return (0);
}

static int	ft_has_equal_sign(char *s)
{
	while (*s)
	{
		if (*s == '=')
			return (1);
		s++;
	}
	return (0);
}
