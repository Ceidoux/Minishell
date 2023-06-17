/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:41:04 by smestre           #+#    #+#             */
/*   Updated: 2023/06/16 17:41:03 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*remove_path(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '/')
			j = i;
		i++;
	}
	res = malloc(sizeof(char) * (ft_strlen(str) - j));
	if (res == NULL)
		return (NULL);
	j++;
	i = 0;
	while (str[j])
		res[i++] = str[j++];
	res[i] = 0;
	free(str);
	return (res);
}

void	no_execution(t_tools tools)
{
	dup2(tools.saved_std_out, 1);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("Command not found : %s \n", tools.args[0]);
	free_all(tools);
	free_main(&tools);
	exit(0);
}

int	end_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == '/')
		return (1);
	return (0);
}

char	*ft_strdup(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (1 + ft_strlen(str)));
	if (res == NULL)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

void	free_main(t_tools *tools)
{
	tools->i = 0;
	while (tools->pipe_fd[tools->i])
	{
		free(tools->pipe_fd[tools->i]);
		(tools->i)++;
	}
	free(tools->pipe_fd);
	free(tools->pid);
}
