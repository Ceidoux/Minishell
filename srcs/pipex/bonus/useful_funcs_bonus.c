/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:35:18 by smestre           #+#    #+#             */
/*   Updated: 2023/06/16 17:35:48 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_putchar(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	ft_putstr(char *str, int *len)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		*len += 6;
		return ;
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		(*len)++;
	}
}

void	ft_putnbr(int nbr, int *len)
{
	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		*len += 11;
		return ;
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr *= -1;
		(*len)++;
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10, len);
		nbr = (nbr % 10) + '0';
		write(1, &nbr, 1);
		(*len)++;
	}
	else
	{
		nbr += '0';
		write(1, &nbr, 1);
		(*len)++;
	}
}

void	ft_putunsnbr(unsigned int nbr, int *len)
{
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10, len);
		nbr = (nbr % 10) + '0';
		write(1, &nbr, 1);
		(*len)++;
	}
	else
	{
		nbr += '0';
		write(1, &nbr, 1);
		(*len)++;
	}
}

void	ft_putnbr_base(unsigned int nbr, char *base, int *len)
{
	if (nbr / 16 != 0)
		ft_putnbr_base(nbr / 16, base, len);
	write(1, &base[nbr % 16], 1);
	(*len)++;
}
