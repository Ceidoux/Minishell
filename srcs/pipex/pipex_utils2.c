/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:23:16 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 14:36:42 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_len_before_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	is_builtin(char *str, char **envp)
{
	char	*copy;

	copy = NULL;
	copy = ft_strdup(str);
	ft_expand(&copy, envp);
	ft_unquote(&copy);
	if (ft_strcmp(copy, "cd") || ft_strcmp(copy, "echo")
		|| ft_strcmp(copy, "env") || ft_strcmp(copy, "exit")
		|| ft_strcmp(copy, "export") || ft_strcmp(copy, "pwd")
		|| ft_strcmp(copy, "unset"))
	{	
		free(copy);
		return (1);
	}
	free(copy);
	return (0);
}

void	is_double_quote(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
		(*i)++;
	if (str[*i])
		(*i)++;
}

void	is_single_quote(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i])
		(*i)++;
}

void	is_quote(char *str, int *i)
{
	if (str[*i] == '\"')
		is_double_quote(str, i);
	else if (str[*i] == '\'')
		is_single_quote(str, i);
	else
		(*i)++;
}
