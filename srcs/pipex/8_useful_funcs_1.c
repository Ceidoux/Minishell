/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_useful_funcs_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:35:18 by smestre           #+#    #+#             */
/*   Updated: 2023/07/04 01:49:34 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	pipex_putchar(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	error_pipex_putchar(char c, int *len)
{
	write(2, &c, 1);
	(*len)++;
}

void	pipex_putstr(char *str, int *len)
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

void	error_pipex_putstr(char *str, int *len)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(2, "(null)", 6);
		*len += 6;
		return ;
	}
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
		(*len)++;
	}
}

void	pipex_putnbr(int nbr, int *len)
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
		pipex_putnbr(nbr / 10, len);
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

void	error_pipex_putnbr(int nbr, int *len)
{
	if (nbr == -2147483648)
	{
		write(2, "-2147483648", 11);
		*len += 11;
		return ;
	}
	if (nbr < 0)
	{
		write(2, "-", 1);
		nbr *= -1;
		(*len)++;
	}
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

void	pipex_putunsnbr(unsigned int nbr, int *len)
{
	if (nbr >= 10)
	{
		pipex_putnbr(nbr / 10, len);
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

void	pipex_putnbr_base(unsigned int nbr, char *base, int *len)
{
	if (nbr / 16 != 0)
		pipex_putnbr_base(nbr / 16, base, len);
	write(1, &base[nbr % 16], 1);
	(*len)++;
}

void	error_pipex_putnbr_base(unsigned int nbr, char *base, int *len)
{
	if (nbr / 16 != 0)
		error_pipex_putnbr_base(nbr / 16, base, len);
	write(2, &base[nbr % 16], 1);
	(*len)++;
}
