/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_6_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:34:45 by smestre           #+#    #+#             */
/*   Updated: 2023/06/16 19:16:27 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_before(t_tools *tools)
{
	int	i;

	i = 0;
	while (i < tools->i)
		free(tools->pipe_fd[i++]);
	free(tools->pipe_fd);
}

void	get_next_path(char *full_line, int fd)
{
	free(full_line);
	full_line = get_next_line(fd);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*path_line(char **envp)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	k = 0;
	i = 0;
	j = 5;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5))
		{
			res = malloc(sizeof(char) * (ft_strlen(envp[i]) - 4));
			while (envp[i][j])
				res[k++] = envp[i][j++];
			res[k] = 0;
			return (res);
		}
		i++;
	}
	return (NULL);
}

void	no_path(t_tools tools)
{
	dup2(tools.saved_std_out, 1);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("Command not found : %s \n", tools.args[0]);
	free_no_path(tools);
	free_main(&tools);
	exit(0);
}
