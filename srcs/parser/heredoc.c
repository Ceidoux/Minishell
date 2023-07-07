/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:00:40 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/06 19:33:45 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_create_heredoc(char *delimiter, char **envp);
static int	ft_realdine_heredoc(char *delimiter, char **envp, int fd);

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
	int		tp_exit_status;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (-1);
	tp_exit_status = g_exit_status;
	g_exit_status = -1;
	if (ft_realdine_heredoc(delimiter, envp, fd) == -1)
		return (close(fd), -1);
	g_exit_status = tp_exit_status;
	close(fd);
	return (0);
}

static int	ft_realdine_heredoc(char *delimiter, char **envp, int fd)
{
	int		idx;
	char	*line;

	idx = 0;
	line = NULL;
	while (++idx)
	{
		line = readline(">");
		if (g_exit_status == 130)
			return (free(line), -1);
		else if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		if (idx > 1)
			write(fd, "\n", 1);
		ft_expand(&line, envp);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	write(fd, "\n", 1);
	free(line);
	return (0);
}

/*
export VAR=END
cat << $VAR		-> le délimitateur est $VAR
cat << "$VAR" 	-> le délimitateur est VAR
cat << $"VAR" 	-> le délimitateur est VAR
*/
