/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_ft_split_slash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:27:20 by kali              #+#    #+#             */
/*   Updated: 2023/06/23 10:19:31 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

char	**pipex_split_slash(char *str, char charset)
{
	char	**res;
	int		i;
	int		j;
	int		ancre;

	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * (1 + count_words(str, charset)));
	if (res == NULL)
		return (NULL);
	res[count_words(str, charset)] = NULL;
	while (str[i])
	{
		if (not_blank(str[i], charset))
		{
			ancre = i;
			while (str[i] && not_blank(str[i], charset))
				i++;
			res[j] = put_word_slash(str, ancre, i);
			j++;
		}
		else
			i++;
	}
	return (res);
}

char	*put_word_slash(char *str, int start, int end)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (end - start + 2));
	if (res == NULL)
		return (NULL);
	while (start < end)
	{
		res[i] = str[start];
		start++;
		i++;
	}
	res[i] = '/';
	i++;
	res[i] = '\0';
	return (res);
}

