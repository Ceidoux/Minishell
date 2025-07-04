/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:49:08 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 14:02:18 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_unset_my_var(char *varname, char **old_envp);

char	**ft_unset(char *s, char **envp)
{
	char	**var_tab;
	int		idx;

	if (!envp)
		return (NULL);
	var_tab = ft_split(s, ' ');
	idx = 0;
	while (var_tab[++idx])
		envp = ft_unset_my_var(var_tab[idx], envp);
	while (--idx >= 0)
		free(var_tab[idx]);
	free(var_tab);
	return (envp);
}

static char	**ft_unset_my_var(char *varname, char **old_envp)
{
	char	**new_envp;
	int		old_size;
	int		offset;

	if (env_var_exists(old_envp, varname))
	{
		old_size = ft_envp_size(old_envp);
		new_envp = malloc((old_size) * sizeof(*new_envp));
		if (!new_envp)
			exit(EXIT_FAILURE);
		new_envp[old_size - 1] = NULL;
		offset = 0;
		while (--old_size >= 0)
		{
			if (!ft_strncmp(varname, old_envp[old_size], ft_strlen(varname))
				&& (old_envp[old_size][ft_strlen(varname)] == '='
				|| old_envp[old_size][ft_strlen(varname)] == '\0'))
				offset = 1;
			else
				new_envp[old_size - 1 + offset] = ft_strdup(old_envp[old_size]);
		}
		return (ft_envp_free(old_envp), new_envp);
	}
	else
		return (old_envp);
}
