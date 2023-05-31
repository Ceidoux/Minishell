/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:03:05 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/14 12:54:37 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	s1_len = 0;
	s2_len = 0;
	while (s1[s1_len])
		s1_len++;
	while (s2[s2_len])
		s2_len++;
	ret = malloc((s1_len + s2_len + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	ret[s1_len + s2_len] = '\0';
	while (s2_len--)
		ret[s1_len + s2_len] = s2[s2_len];
	while (s1_len--)
		ret[s1_len] = s1[s1_len];
	return (ret);
}
