/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:03:24 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/14 12:54:34 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s)
		if (*s++ == (unsigned char)c)
			i = 1;
	if (!((unsigned char)c))
		return ((char *)s);
	if (!i)
		return (0);
	while (*s != (unsigned char)c)
		s--;
	return ((char *)s);
}
