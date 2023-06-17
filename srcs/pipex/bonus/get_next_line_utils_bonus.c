/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:15:47 by smestre           #+#    #+#             */
/*   Updated: 2023/06/16 17:28:27 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (res);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
	free(s1);
	return (res);
}

int	ft_strlcpy(char *dst, const char *src, int size)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(dst);
	while (ft_strlen(dst))
	{
		dst[j] = 0;
		j--;
	}
	if (size <= 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}

void	ft_bzero(void *s, int n)
{
	int				i;
	unsigned char	*s2;

	i = 0;
	s2 = (unsigned char *) s;
	while (i < n)
	{
		s2[i] = 0;
		i++;
	}
}

void	ft_copy(char *line, char *buf)
{
	if (buf != NULL)
		ft_strlcpy(line, buf, ft_strlen(buf) + 1);
}
