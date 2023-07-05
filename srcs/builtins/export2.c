/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:15:51 by smestre           #+#    #+#             */
/*   Updated: 2023/07/05 14:27:25 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"


// la suite de separation_two. Ces deux fonctions servent a faire un split mais
// que pour la premiere instance du charset, divisant le tableau en 2

char	**split_two(char *str, int i)
{
	int		j;
	char	**res;

	res = malloc(sizeof(char *) * 3);
	res[2] = NULL;
	j = 0;
	res[0] = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		res[0][j] = str[j];
		j++;
	}
	res[0][j] = 0;
	j = 0;
	res[1] = malloc(sizeof(char) * (ft_strlen(str) - i));
	i++;
	while (str[i])
	{
		res[1][j] = str[i];
		i++;
		j++;
	}
	res[1][j] = 0;
	return (res);
}
/* voir split_two*/

char	**separate_two(char	*str)
{
	char	**res;
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_char(str[i], '=') && (size_t)i != (ft_strlen(str) - 1))
		{
			res = split_two(str, i);
			return (res);
		}
		i++;
	}
	res = malloc(sizeof(char *) * 2);
	res[1] = NULL;
	res[0] = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	while ((size_t)i < ft_strlen(str) - 1)
	{
		res[0][i] = str[i];
		i++;
	}
	res[0][i] = 0;
	return (res);
}
/* permet de savoir combien de caracters avant le premier signe '='
 (utile pour savoir s la variable existe deja avec strncmp() )*/

int	ft_len_dif(char *str)
{
	int	i;

	i = 0;
	if (has_car(str, '=') != -1)
	{
		while (str[i] != '=')
			i++;
		return (i);
	}
	else
		return (ft_strlen(str));
}
/* permet de savoir si l'enchainement "+="  est present dans la string*/

int	plus_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
		{
			i++;
			if (str[i] == '=')
				return (1);
			return (0);
		}
		i++;
	}
	return (-1);
}
/* verifie que la variable exportee respecte bien les regles de syntaxe */

int	has_invalid_character(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '=')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if ((str[i] < 'A'
				|| str[i] > 'Z') && (str[i] < 'a'
				|| str[i] > 'z') && (str[i] < '0' || str[i] > '9')
			&& str[i] != '_' && str[i] != '='
			&& plus_equal(str) != 1)
			return (1);
		i++;
	}
	return (0);
}
