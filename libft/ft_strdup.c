/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:03:01 by jleguay           #+#    #+#             */
/*   Updated: 2023/06/30 22:12:36 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = 0;
	while (s1[len])
		len++;
	s2 = malloc(sizeof(*s2) * (len + 1));
	if (!s2)
		return (NULL);
	s2[len] = '\0';
	while (len--)
		s2[len] = s1[len];
	return (s2);
}
