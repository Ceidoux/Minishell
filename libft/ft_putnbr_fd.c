/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:02:53 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/14 12:54:39 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		sign;
	char	c;

	sign = 1;
	if (n < 0)
	{
		write (fd, "-", 1);
		sign = -1;
	}
	if (n > 9 || n < -9)
		ft_putnbr_fd(n / 10 * sign, fd);
	c = n % 10 * sign + '0';
	write(fd, &c, 1);
}
