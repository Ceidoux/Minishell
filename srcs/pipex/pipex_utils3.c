/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:23:26 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 14:29:53 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	double_quote(char *str, int *i, int *flag, int *compteur)
{
	(*i)++;
	if (*flag == 0)
	{
		(*compteur)++;
		*flag = 1;
	}
	while (str[*i] && str[*i] != '\"')
		(*i)++;
	if (str[*i])
		(*i)++;
}

void	single_quote(char *str, int *i, int *flag, int *compteur)
{
	(*i)++;
	if (*flag == 0)
	{
		(*compteur)++;
		*flag = 1;
	}
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i])
		(*i)++;
}
