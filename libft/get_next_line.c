/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle <jle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:51:34 by jleguay           #+#    #+#             */
/*   Updated: 2023/04/28 22:26:39 by jle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	t_current		current;
	static t_lst	lst;

	current.buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!current.buff)
		return (NULL);
	current.buff[0] = '\0';
	current.line = gnl_get_current(lst.next_line);
	lst.next_line = gnl_get_next(lst.next_line);
	if (!current.line || (lst.eof == 1 && current.line[0] == '\0'))
		return (free(current.buff), free(current.line), NULL);
	if (current.line[gnl_eol(current.line)] == '\n')
		return (free(current.buff), current.line);
	current.line = gnl_loop(&current, &lst, fd);
	if (!current.line)
		return (NULL);
	lst.next_line = gnl_remainer(lst.next_line, current.buff, current.eol);
	return (free(current.buff), current.line);
}

char	*gnl_loop(t_current *current, t_lst *lst, int fd)
{
	(*current).eol = BUFFER_SIZE;
	while ((*current).eol == BUFFER_SIZE && !(*lst).eof)
	{
		(*current).eol = read(fd, (*current).buff, BUFFER_SIZE);
		if ((*current).eol == -1 || BUFFER_SIZE <= 0
			|| (!(*current).eol && !(*current).line[0]))
			return (free((*current).buff), free((*current).line), NULL);
 		(*current).buff[(*current).eol] = '\0';
		(*current).eol = gnl_eol((*current).buff);
		(*current).line = gnl_join((*current).line,
				(*current).buff, (*current).eol);
	}
	return ((*current).line);
}
