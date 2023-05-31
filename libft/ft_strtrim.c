/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle <jle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:03:26 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/20 19:21:31 by jle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char const *set, char c)
{
	size_t	i;

	i = -1;
	while (set[++i])
		if (set[i] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	l;
	size_t	i;
	char	*ret;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	l = 0;
	while (s1[i] && isset(set, s1[i]))
		i++;
	if (s1[i])
	{
		l++;
		while (s1[++i])
			l++;
		while (i-- > 0 && isset(set, s1[i]))
			l--;
	}
	ret = malloc((l + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	ret[l] = '\0';
	while (l--)
		ret[l] = s1[i--];
	return (ret);
}
