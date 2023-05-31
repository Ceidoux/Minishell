/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle <jle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:02:16 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/20 19:20:28 by jle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ret_len(unsigned int n)
{
	if (n < 10)
		return (1);
	return (1 + ret_len(n / 10));
}

char	*ft_itoa(int n)
{
	char			*ret;
	unsigned int	len;
	int				sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	len = ret_len(sign * n) + (sign - 1) / (-2);
	ret = malloc((len + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	if (!n)
		ret[0] = '0';
	if (n < 0)
		ret[0] = '-';
	while (n)
	{
		ret[--len] = (n % 10) * sign + '0';
		n /= 10;
	}
	return (ret);
}
