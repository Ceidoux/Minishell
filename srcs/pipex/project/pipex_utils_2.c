/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:53:40 by smestre           #+#    #+#             */
/*   Updated: 2023/06/16 17:41:23 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	syntax_help(void)
{
	ft_printf("Error : Wrong Number of arguments.\n");
	ft_printf("Syntax should be as follows : ");
	ft_printf("FILE1 CMD1 PARAMS1 CMD2 PARAMS2 FILE2\n");
	return (1);
}

int	non_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 0 && str[i] <= 32) || str[i] == 127)
			i++;
		else
			return (0);
	}
	return (1);
}
