/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:03:29 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/14 12:54:33 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	l;

	if (!s)
		return (NULL);
	l = 0;
	while (*(s + l) && l < start)
		l++;
	if (l < start)
		l = 0;
	else
	{
		l = 0;
		while (*(s + start + l) && l < len)
			l++;
	}
	ret = malloc((l + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	ret[l] = '\0';
	while (l--)
		ret[l] = s[start + l];
	return (ret);
}
