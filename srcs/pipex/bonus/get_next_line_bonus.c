/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:39:26 by smestre           #+#    #+#             */
/*   Updated: 2023/06/16 17:25:57 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	end_of_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*real_line(char *line, char *buf, int error)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (error < BUFFER_SIZE && !end_of_line(line))
		return (line);
	while (line[i] != '\n' && line[i])
		i++;
	i++;
	res = malloc(sizeof(char) * (i + 1));
	if (res == NULL)
		return (NULL);
	while (++j < i)
		res[j] = line[j];
	res[j] = 0;
	ft_bzero(buf, BUFFER_SIZE);
	j = 0;
	while (line[i])
		buf[j++] = line[i++];
	buf[j] = 0;
	return (free(line), res);
}

void	clear_buf(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		buf[i] = 0;
		i++;
	}
}

char	*ft_calloc(void)
{
	char	*res;

	res = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, BUFFER_SIZE + 1);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			error;

	if (BUFFER_SIZE == 0 || fd < 0)
		return (NULL);
	error = BUFFER_SIZE;
	line = ft_calloc();
	if (line == NULL)
		return (NULL);
	ft_copy(line, buf);
	while (!end_of_line(line))
	{
		ft_bzero(buf, BUFFER_SIZE);
		error = read(fd, buf, BUFFER_SIZE);
		if (error <= 0 && line[0] == 0)
		{
			free(line);
			return (NULL);
		}
		if (error <= 0)
			return (line);
		line = ft_strjoin(line, buf);
	}
	return (real_line(line, buf, error));
}
