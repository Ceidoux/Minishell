/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:54 by smestre           #+#    #+#             */
/*   Updated: 2023/07/06 14:57:25 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

//retire le '+' dune string
char	*remove_plus(char *str)
{
	int		i;
	char	**cut;
	char	*res;

	res = ft_strdup(str);
	i = 1;
	if (has_car(res, '+') != -1)
	{
		cut = ft_split(res, '+');
		while (cut[i])
		{
			cut[0] = pipex_strjoin(cut[0], cut[i]);
			i++;
		}
		i = 1;
		while (cut[i])
			free(cut[i++]);
		free(res);
		res = pipex_strdup(cut[0]);
		free(cut);
	}
	return (res);
}
//remplace la variable dans envp par la nouvelle variable

char	**ft_addstr_replace(char **envp, char *str, int i)
{
	free(envp[i]);
	envp[i] = ft_strdup(str);
	return (envp);
}

//concatene

char	**ft_addstr_plus(char **res, char **envp, char *str, int i)
{
	int		j;

	j = 0;
	res = separate_two(str);
	if (has_car(envp[i], '=') == -1)
		envp[i] = pipex_strjoin(envp[i], "=");
	if (env_size(res) > 1)
		envp[i] = pipex_strjoin(envp[i], res[1]);
	while (res[j])
		free(res[j++]);
	free(res);
	return (envp);
}

//permet de ajouter la variable dans envp !
// str = modify_var(str); apres res = NULL

char	**ft_addstr(char **envp, char *str, int envp_size)
{
	int		i;
	char	**res;
	char	*str_no_plus;

	i = 0;
	res = NULL;
	str_no_plus = remove_plus(str);
	while (envp[i])
	{
		if (pipex_strncmp(str, envp[i], ft_len_dif(str))
			&& has_car(str, '=') == -1
			&& ft_len_dif(str) == ft_len_dif(envp[i]))
			{
				free(str_no_plus);
				return (envp);
			}
		if (pipex_strncmp(str, envp[i], ft_len_dif(str))
			&& ft_len_dif(str) == ft_len_dif(envp[i]))
			{
				free(str_no_plus);
				return (ft_addstr_replace(envp, str, i));
			}
		if (pipex_strncmp(str_no_plus, envp[i],
				ft_len_dif(str_no_plus)) && plus_equal(str) == 1)
			{
				free(str_no_plus);
				return (ft_addstr_plus(res, envp, str, i));
			}
		i++;
	}
	free(str_no_plus);
	res = ft_addstr_end(envp, str, envp_size);
	return (res);
}

char	**ft_addstr_end(char **envp, char *str, int envp_size)
{
	int		i;
	char	**res;
	char	*str_no_plus;

	i = 0;
	str_no_plus = remove_plus(str);
	res = malloc(sizeof(char *) * (envp_size + 2));
	ft_bzero(res, sizeof(char *) * (envp_size + 2));
	res[envp_size + 1] = NULL;
	while (envp_size > 0)
	{
		res[envp_size - 1] = ft_strdup(envp[envp_size - 1]);
		free(envp[envp_size - 1]);
		i++;
		envp_size--;
	}
	res[i] = pipex_strdup(str_no_plus);
	free(envp);
	return (res);
}
