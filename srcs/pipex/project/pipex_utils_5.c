/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:18:00 by smestre           #+#    #+#             */
/*   Updated: 2023/06/15 09:52:56 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*return_full_line(char *full_line, char *res, int fd)
{
	close(fd);
	return (free(res), full_line);
}

void	get_next_path(char *full_line, int fd)
{
	free(full_line);
	full_line = get_next_line(fd);
}
