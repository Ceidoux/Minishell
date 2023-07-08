/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:23:06 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 14:36:40 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	env_var_exists(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (((size_t)ft_len_before_equal(envp[i]) == ft_strlen(str)
				&& ft_strncmp(envp[i], str, ft_len_before_equal(envp[i])) == 0))
			return (1);
		i++;
	}
	return (0);
}

char	*get_path(char **envp, char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (envp[i])
	{
		if ((ft_strlen(envp[i]) == ft_strlen(str)
				&& ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			|| ft_strncmp(envp[i], str, 5) == 0)
		{
			res = ft_strdup(envp[i]);
			return (res);
		}
		i++;
	}
	return (NULL);
}

char	*remove_beginning(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	res = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (res == NULL)
		return (NULL);
	while (str[i])
		res[j++] = str[i++];
	res[j] = 0;
	free(str);
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strsort(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s2[i] - s1[i]);
		i++;
	}
	return (0);
}
