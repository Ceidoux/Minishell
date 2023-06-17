/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:37:03 by smestre           #+#    #+#             */
/*   Updated: 2023/06/16 17:25:09 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char	*finding_path(void)
{
	int		fd;
	char	*full_line;
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * 6);
	fd = open("/etc/environment", O_RDONLY);
	full_line = get_next_line(fd);
	while (full_line)
	{
		while (full_line[i] && i < 5)
		{
			res[i] = full_line[i];
			i++;
		}
		res[i] = 0;
		if (ft_strcmp(res, "PATH="))
			return (return_full_line(full_line, res, fd));
		else
			get_next_path(full_line, fd);
		i = 0;
	}
	close(fd);
	return (free(res), NULL);
}

char	*ft_trim(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 5;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) - 4));
	if (res == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\n')
		{
		res[j] = str[i];
			i++;
			j++;
		}
		else
			i++;
	}
	res[j] = 0;
	free(str);
	return (res);
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

void	free_first(t_tools tools)
{
	int	i;

	i = 0;
	free(tools.str);
	while (tools.paths[i])
		free(tools.paths[i++]);
	free(tools.paths);
}
