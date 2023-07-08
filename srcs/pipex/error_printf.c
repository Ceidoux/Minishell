/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:13:04 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 14:29:23 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	error_pipex_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
			print_format((char *)str, &i, args, &len);
		else
		{
			error_pipex_putchar(str[i], &len);
			i++;
		}
	}
	va_end(args);
	return (len);
}

void	error_pipex_putpoint_base(long unsigned int nbr, char *base, int *len)
{
	if (nbr == 0)
	{
		write(2, "(nil)", 5);
		*len += 5;
		return ;
	}
	write(2, "0x", 2);
	(*len) += 2;
	error_pipex_putlongnbr_base(nbr, base, len);
}

void	error_pipex_putchar(char c, int *len)
{
	write(2, &c, 1);
	(*len)++;
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
