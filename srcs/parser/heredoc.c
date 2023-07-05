/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:00:40 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/05 16:59:33 by jleguay          ###   ########.fr       */
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
	int		tp_exit_status;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (-1);
	idx = 0;
	tp_exit_status = g_exit_status;
	g_exit_status = 0;
	while (++idx)
	{
		line = readline(">");
		// ft_putnbr_fd(g_exit_status, 1);
		if (g_exit_status == 130)
			return (-1);
		// else if (!line)
		// {
		// 	write(1, "\n", 1);
		// 	break;
		// }
		else if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		else if (idx > 1)
			write(fd, "\n", 1);
		ft_expand(&line, envp);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	write(fd, "\n", 1);
	g_exit_status = tp_exit_status;
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
