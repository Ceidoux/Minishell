/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_ft_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:34:03 by kali              #+#    #+#             */
/*   Updated: 2023/07/07 15:50:33 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	not_blank(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	count_words(char *str, char *charset)
{
	int	compteur;
	int	flag;
	int	i;

	i = 0;
	compteur = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			if (flag == 0)
			{
				compteur++;
				flag = 1;
			}
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i])
				i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			if (flag == 0)
			{
				compteur++;
				flag = 1;
			}
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i])
				i++;
		}
		else if (not_blank(str[i], charset) && flag == 0)
		{
			compteur++;
			flag = 1;
			i++;
		}
		else if (!not_blank(str[i], charset))
		{
			flag = 0;
			i++;
		}
		else if (str[i])
			i++;
	}
	return (compteur);
}

char	*put_word(char *str, int start, int end)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (end - start + 1));
	if (res == NULL)
		return (NULL);
	while (start < end)
	{
		res[i] = str[start];
		start++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**pipex_split(char *str, char *charset)
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
			{
				if (str[i] == '\"')
				{
					i++;
					while (str[i] && str[i] != '\"')
						i++;
					if (str[i])
						i++;
				}
				else if (str[i] == '\'')
				{
					i++;
					while (str[i] && str[i] != '\'')
						i++;
					if (str[i])
						i++;
				}
				else
					i++;
			}
			res[j] = put_word(str, ancre, i);
			j++;
		}
		else
			i++;
	}
	return (res);
}
