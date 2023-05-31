/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle <jle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:22:17 by jleguay           #+#    #+#             */
/*   Updated: 2023/05/07 18:01:10 by jle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_lst
{
	char	*next_line;
	int		eof;
}	t_lst;

typedef struct s_current
{
	char	*buff;
	char	*line;
	int		eol;
}	t_current;

char	*get_next_line(int fd);
char	*gnl_loop(t_current *current, t_lst *lst, int fd);
char	*gnl_get_current(char *next_line);
char	*gnl_get_next(char *next_line);
int		gnl_eol(char *buff);
char	*gnl_join(char *end, char *start, int size);
char	*gnl_remainer(char *next_line, char *buff, int eol);
int		gnl_has_eol(char *line);

#endif
