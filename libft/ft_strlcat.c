/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:03:08 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/14 12:54:36 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dstsize && dst[i])
	{
		dstsize--;
		i++;
	}
	j = -1;
	while (src[++j] && dstsize-- > 1)
		dst[i + j] = src[j];
	if (j)
		dst[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}
