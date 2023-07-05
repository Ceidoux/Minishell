/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:00:40 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/01 17:06:58 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_create_heredoc(char *delimiter, char **envp);

int	ft_heredoc(char *delimiter, char **envp)
{
	int	fd;

	if (ft_create_heredoc(delimiter, envp) == -1)
		return (-1);
	fd = open(".heredoc", O_RDONLY);
	if (fd == -1)
		return (-1);
	unlink(".heredoc");
	return (fd);
}

static int	ft_create_heredoc(char *delimiter, char **envp)
{
	int		fd;
	char	*line;
	int		idx;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (-1);
	idx = 0;
	while (++idx)
	{
		line = readline(">");
		if (g_exit_status == 130)				// Ctrl-C
			return (free(line), close(fd), -1);
		if (!line)								// Ctrl-D
			write(1, "\n", 1);
		if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		if (idx > 1)
			write(fd, "\n", 1);
		ft_expand(&line, envp);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	write(fd, "\n", 1);
	free(line);
	close(fd);
	return (0);
}
/*
export VAR=END
cat << $VAR		-> le délimitateur est $VAR
cat << "$VAR" 	-> le délimitateur est VAR
cat << $"VAR" 	-> le délimitateur est VAR
*/
