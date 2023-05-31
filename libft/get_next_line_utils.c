/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:51:50 by jleguay           #+#    #+#             */
/*   Updated: 2022/12/21 15:43:33 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_get_current(char *next_line)
{
	char	*current;
	int		len;

	if (!next_line)
	{
		current = malloc(sizeof(char));
		if (!current)
			return (NULL);
		current[0] = '\0';
	}
	else
	{
		len = gnl_eol(next_line) + 1;
		current = malloc((len + 1) * sizeof(char));
		if (!current)
			return (NULL);
		current[len] = '\0';
		while (--len >= 0)
			current[len] = next_line[len];
	}
	return (current);
}

char	*gnl_get_next(char *next_line)
{
	char	*next;
	int		len;
	int		eol;

	if (!next_line)
		return (NULL);
	eol = gnl_eol(next_line);
	len = 0;
	while (next_line[eol + len])
		len++;
	if (len)
	{
		next = malloc((len + 1) * sizeof(char));
		if (!next)
			return (NULL);
		next[len] = '\0';
		while (len--)
			next[len] = next_line[eol + 1 + len];
		return (free(next_line), next);
	}
	free(next_line);
	next_line = NULL;
	return (NULL);
}

int	gnl_eol(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] && i < BUFFER_SIZE)
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*gnl_join(char *start, char *end, int size)
{
	int		len_start;
	int		len_end;
	char	*joined;

	len_start = 0;
	len_end = 0;
	while (start[len_start])
		len_start++;
	while (end[len_end] && len_end <= size)
		len_end++;
	joined = malloc((len_start + len_end + 1) * sizeof(char));
	if (!joined)
		return (free(start), NULL);
	joined[len_start + len_end] = '\0';
	while (len_end--)
		joined[len_start + len_end] = end[len_end];
	while (len_start--)
		joined[len_start] = start[len_start];
	return (free(start), joined);
}

char	*gnl_remainer(char *next_line, char *buff, int eol)
{
	int		length;

	length = 0;
	while (buff[length])
		length++;
	length = length - eol - 1;
	if (length <= 0)
		return (NULL);
	next_line = malloc((length + 1) * sizeof(char));
	if (!next_line)
		return (NULL);
	next_line[length] = '\0';
	while (length--)
		next_line[length] = buff[eol + 1 + length];
	return (next_line);
}
