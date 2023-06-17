/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:46:24 by smestre           #+#    #+#             */
/*   Updated: 2023/06/16 16:20:21 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
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

void	free_all(t_tools tools)
{
	int	i;

	i = 0;
	free(tools.str);
	while (tools.paths[i])
		free(tools.paths[i++]);
	free(tools.paths);
	i = 0;
	while (tools.args[i])
		free(tools.args[i++]);
	free(tools.args);
}

void	free_no_path(t_tools tools)
{
	int	i;

	i = 0;
	while (tools.args[i])
		free(tools.args[i++]);
	free(tools.args);
}
