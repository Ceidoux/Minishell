/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:03:15 by jleguay           #+#    #+#             */
/*   Updated: 2023/06/25 03:58:54 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (!++n)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
