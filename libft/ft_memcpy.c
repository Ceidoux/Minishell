/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:02:44 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/14 12:54:41 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*cpy;

	if (!dst && !src)
		return (NULL);
	cpy = dst;
	while (n-- > 0)
		*cpy++ = *(char *)src++;
	return (dst);
}
