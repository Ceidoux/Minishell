/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:04:20 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/05 19:45:05 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envp_size(char **envp)
{
	int		size;

	size = 0;
	if (envp)
	{
		while (envp[size])
			size++;
	}
	return (size);
}

char	**ft_envp_realloc(char **old_envp, size_t new_size)
{
	char	**new_envp;
	int		old_size;

	old_size = ft_envp_size(old_envp);
	new_envp = malloc(new_size * sizeof(*new_envp));
	if (!new_envp)
		exit(EXIT_FAILURE);
	new_envp[old_size] = NULL;
	while (--old_size >= 0)
	{
		new_envp[old_size] = ft_strdup(old_envp[old_size]);
		free(old_envp[old_size]);
	}
	free(old_envp);
	return (new_envp);
}

void	ft_envp_free(char **envp)
{
	int	i;

	i = -1;
	if (envp)
	{
		while (envp[++i])
			free(envp[i]);
		free(envp);
		envp = NULL;
	}
}

char	**ft_envp_dup(char **envp)
{
	int		size;
	char	**envp_dup;

	size = ft_envp_size(envp);
	if (!size)
		return (NULL);
	envp_dup = malloc((size + 1) * sizeof(*envp_dup));
	if (!envp_dup)
		exit(EXIT_FAILURE);
	envp_dup[size] = NULL;
	while (--size >= 0)
		envp_dup[size] = ft_strdup(envp[size]);
	return (envp_dup);
}

char	*ft_getenv(char *var, char **envp)
{
	int	idx;

	idx = -1;
	if (envp)
	{
		while (envp[++idx])
			if (!ft_strncmp(envp[idx], var, ft_strlen(var)) && envp[idx][ft_strlen(var)] == '=')
				return (envp[idx] + ft_strlen(var) + 1);
	}
	return (NULL);
}
