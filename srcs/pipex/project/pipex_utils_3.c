/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:48:27 by smestre           #+#    #+#             */
/*   Updated: 2023/06/15 09:19:02 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	free_str_args(t_tools tools)
{
	int	i;

	i = 0;
	while (tools.args[i])
	{
		free(tools.args[i]);
		i++;
	}
	free(tools.args);
	free(tools.str);
}

int	is_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
