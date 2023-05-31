/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:49:50 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/14 12:54:48 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	size_t	j;
	void	*ret;

	if (!count || !size)
		return (malloc(0));
	if (count > SIZE_MAX / size)
		return (NULL);
	ret = malloc(size * count);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		j = 0;
		while (j < size)
			*(char *)(ret + i * size + j++) = 0;
	}
	return (ret);
}
