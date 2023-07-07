/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_paths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:31:07 by kali              #+#    #+#             */
/*   Updated: 2023/07/07 15:50:11 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*

toutes ces fonctions sont lies aux chemins des commandes. 
remove_path() permet de garder juste le nom de la commande sans le chemin
is_slash() permet de  verifier si il y a bien un "/" dans la commande
end_slash() permet de verifier si la commande se termine par un "/"
no_path() est execute si aucun chemin n'est valide.

*/
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
	res = malloc(sizeof(char) * (pipex_strlen(str) - j));
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

void	no_path(t_tools tools)
{
	error_pipex_printf("%s: No such file or directory\n", tools.args[0]);
	free_no_path(tools);
	free_main(&tools);
	exit(127);
}
