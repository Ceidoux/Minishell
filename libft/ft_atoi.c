/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:50:43 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/14 12:54:49 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str && (*str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r' || *str == ' '))
		str++;
	if (*str == '+' || *str == '-')
		sign *= 44 - *str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		if ((sign == 1 && result > 10 * result + sign * (*str - '0'))
			|| (sign == -1 && result < 10 * result + sign * (*str - '0')))
			return (-(sign + 1) / 2);
		result = 10 * result + sign * (*str++ - '0');
	}
	return (result);
}
