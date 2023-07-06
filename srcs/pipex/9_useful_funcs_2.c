/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_useful_funcs_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:01:49 by kali              #+#    #+#             */
/*   Updated: 2023/07/06 12:28:21 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	pipex_strncmp(char *s1, char *s2, int n)
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

char	*pipex_strdup(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (1 + pipex_strlen(str)));
	if (res == NULL)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	free(str);
	return (res);
}

char	*ft_putstr2(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char ) * (pipex_strlen(str) + 1));
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	pipex_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*pipex_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (pipex_strlen(s1) + pipex_strlen(s2) + 1));
	if (res == NULL)
		return (res);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
	free(s1);
	return (res);
}
