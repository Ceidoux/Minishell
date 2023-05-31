/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:03:14 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/14 12:54:35 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*ret;

	if (!s || !f)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	ret = malloc((len + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	while (len--)
		ret[len] = (*f)(len, s[len]);
	return (ret);
}
