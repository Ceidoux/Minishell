/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:02:42 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/14 12:54:41 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (!n)
		return (0);
	while (n-- && *(unsigned char *)s1++ == *(unsigned char *)s2++)
		if (!n)
			return (0);
	return ((int)(*(unsigned char *)--s1 - *(unsigned char *)--s2));
}
