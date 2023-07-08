/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printf2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:17:36 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 14:29:27 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	error_pipex_putunsnbr(unsigned int nbr, int *len)
{
	if (nbr >= 10)
	{
		error_pipex_putnbr(nbr / 10, len);
		nbr = (nbr % 10) + '0';
		write(2, &nbr, 1);
		(*len)++;
	}
	else
	{
		nbr += '0';
		write(2, &nbr, 1);
		(*len)++;
	}
}

void	error_pipex_putnbr_base(unsigned int nbr, char *base, int *len)
{
	if (nbr / 16 != 0)
		error_pipex_putnbr_base(nbr / 16, base, len);
	write(2, &base[nbr % 16], 1);
	(*len)++;
}

void	error_pipex_putlongnbr_base(long unsigned int nbr, char *base, int *len)
{
	if (nbr / 16 != 0)
		error_pipex_putlongnbr_base(nbr / 16, base, len);
	write(2, &base[nbr % 16], 1);
	(*len)++;
}
