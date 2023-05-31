/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:02:46 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/14 12:54:40 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_cpy;

	if (!dst && !src)
		return (NULL);
	dst_cpy = dst;
	if (dst < src)
	{
		while (len-- > 0)
			*dst_cpy++ = *(char *)src++;
	}
	else
	{
		while (len-- > 0)
			*(dst_cpy + len) = *((char *)src + len);
	}
	return (dst);
}
