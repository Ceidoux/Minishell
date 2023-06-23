/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_ft_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:37:45 by kali              #+#    #+#             */
/*   Updated: 2023/06/23 10:19:36 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

void	pipex_putlongnbr_base(long unsigned int nbr, char *base, int *len)
{
	if (nbr / 16 != 0)
		pipex_putlongnbr_base(nbr / 16, base, len);
	write(1, &base[nbr % 16], 1);
	(*len)++;
}

void	pipex_putpoint_base(long unsigned int nbr, char *base, int *len)
{
	if (nbr == 0)
	{
		write(1, "(nil)", 5);
		*len += 5;
		return ;
	}
	write(1, "0x", 2);
	(*len) += 2;
	pipex_putlongnbr_base(nbr, base, len);
}

void	print_format(char *str, int *i, va_list args, int *len)
{
	(*i)++;
	if (str[*i])
	{
		if (str[*i] == 'c')
			pipex_putchar((char) va_arg(args, int), len);
		else if (str[*i] == 's')
			pipex_putstr(va_arg(args, char *), len);
		else if (str[*i] == 'p')
			pipex_putpoint_base(va_arg(args, long unsigned int),
				"0123456789abcdef", len);
		else if (str[*i] == 'd' || str[*i] == 'i')
			pipex_putnbr(va_arg(args, int), len);
		else if (str[*i] == 'u')
			pipex_putunsnbr(va_arg(args, unsigned int), len);
		else if (str[*i] == 'x')
			pipex_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", len);
		else if (str[*i] == 'X')
			pipex_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF", len);
		else if (str[*i] == '%')
			pipex_putchar('%', len);
	}
	if (str[*i])
		(*i)++;
}

int	pipex_printf(const char *str, ...)
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
			pipex_putchar(str[i], &len);
			i++;
		}
	}
	va_end(args);
	return (len);
}
