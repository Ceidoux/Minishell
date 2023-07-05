/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:56 by smestre           #+#    #+#             */
/*   Updated: 2023/07/05 14:40:16 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*  Me permet d'avoir le nombres d'arguments passe (toos.args)*/

int	arg_size(t_tools tools)
{
	int	i;

	i = 0;
	while (tools.args[i])
		i++;
	return (i);
}

/* Nombre de lignes dans env*/

int	env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

/*  permet de saboir si un caractere est dans une chaine
(notamment pour =, ' ou encore ")*/

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

/*  permet de savoir si un caractere est le meme element)*/

int	is_char(char str, char c)
{
	if (str == c)
		return (1);
	return (0);
}

/* Un simple echange de valeurs de str*/

void	ft_swap(char **s1, char **s2)
{
	char	*temp;

	temp = ft_strdup(*s1);
	*s1 = ft_strdup(*s2);
	*s2 = ft_strdup(temp);
}
