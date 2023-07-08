/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:56 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 14:01:44 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	arg_size(t_tools tools)
{
	int	i;

	i = 0;
	while (tools.args[i])
		i++;
	return (i);
}

int	env_size(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
			i++;
	}
	return (i);
}

int	has_car(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		(i)++;
	}
	return (-1);
}

int	is_char(char str, char c)
{
	if (str == c)
		return (1);
	return (0);
}

void	ft_swap(char **s1, char **s2)
{
	char	*temp;

	temp = pipex_strdup(*s1);
	*s1 = pipex_strdup(*s2);
	*s2 = pipex_strdup(temp);
}
