/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle <jle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:02:57 by jleguay           #+#    #+#             */
/*   Updated: 2022/11/20 19:21:09 by jle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	cw(char const *s, char c)
{
	size_t			i;
	unsigned int	cw;

	i = 0;
	cw = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		cw++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (cw);
}

static void	free_ret(char **ret, unsigned int word)
{
	while (word--)
		free(ret[word]);
	free(ret);
	ret = NULL;
}

static char	*fill_word(char const *s, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	word = malloc((end - start + 1) * sizeof(*word));
	if (!word)
		return (NULL);
	i = -1;
	while (++i < end - start)
		word[i] = s[start + i];
	word[i] = '\0';
	return (word);
}

static void	fill_ret(char **ret, char const *s, char c)
{
	size_t			end;
	size_t			start;
	unsigned int	word;

	word = 0;
	end = 0;
	while (s[end])
	{
		while (s[end] == c)
			end++;
		if (!s[end])
			break ;
		start = end;
		while (s[end] && s[end] != c)
			end++;
		ret[word] = fill_word(s, start, end);
		if (!ret[word++])
			return (free_ret(ret, --word));
	}
	ret[word] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = malloc((cw(s, c) + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	fill_ret(ret, s, c);
	return (ret);
}
