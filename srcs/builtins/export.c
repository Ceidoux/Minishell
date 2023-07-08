/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:49 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 14:01:32 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	pipex_status(t_tools tools, t_cmd toc, char **envp, int size)
{
	if (tools.status_flag == 0 && size > 1)
		export_free_2(tools, toc, envp);
}

char	**ft_export(t_tools tools, t_cmd toc, char **envp)
{
	int		i;
	int		size;
	int		envp_size;
	char	**export_var;

	i = 0;
	export_var = NULL;
	size = arg_size(tools);
	envp_size = env_size(envp);
	if (!envp_size)
		return (g_exit_status = 0, NULL);
	if (size == 1)
	{
		tools.pid[tools.i] = fork();
		if (tools.pid[tools.i] == 0)
		{
			ft_pipe_manager(tools, toc);
			child_export(export_var, envp, i, envp_size);
			export_free_1(tools, toc, envp);
		}
	}
	else
		add_to_env(&tools, &envp, &size, toc);
	pipex_status(tools, toc, envp, size);
	return (g_exit_status = 0, envp);
}

void	child_export(char **export_var, char **envp, int i, int envp_size)
{
	int	j;

	j = 0;
	while (i < envp_size)
	{
		while (j > 0 && ft_strsort(envp[j - 1], envp[j]) < 0)
		{
			ft_swap(&envp[j - 1], &envp[j]);
			j--;
		}
		i++;
		j = i;
	}
	i = -1;
	while (envp[++i])
		print_env(export_var, envp, i);
}

void	print_env(char **export_var, char **envp, int i)
{
	int	j;

	j = 0;
	if (has_car(envp[i], '=') != -1)
	{
		export_var = separate_two(envp[i]);
		if (env_size(export_var) == 2)
			printf("export %s=\"%s\"\n", export_var[0], export_var[1]);
		else if (env_size(export_var) == 1
			&& envp[i][ft_strlen(envp[i]) - 1] == '=')
			printf("export %s=\"\"\n", export_var[0]);
		while (export_var[j])
			free(export_var[(j)++]);
		free(export_var);
	}
	else
		printf("export %s\n", envp[i]);
}

void	add_to_env(t_tools *tools, char ***envp, int *size, t_cmd toc)
{
	int		i;
	int		envp_size;

	i = 0;
	envp_size = env_size(*envp);
	while (i < *size - 1)
	{
		if (has_invalid_character(tools->args[i + 1]))
			export_not_valid(tools, toc, envp, &i);
		else
		{
			*envp = ft_addstr(*envp, tools->args[i + 1], envp_size);
			envp_size = env_size(*envp);
		}
		i++;
	}
}
