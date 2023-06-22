#include "minishell.h"

static int	ft_create_heredoc(char *delimiter);

int	ft_heredoc(char *delimiter)
{
	int	fd;

	if (ft_create_heredoc(delimiter) == -1)
		return (-1);
	fd = open(".heredoc", O_RDONLY);
	if (fd == -1)
		return (-1);
	unlink(".heredoc");
	return (fd);
}

static int	ft_create_heredoc(char *delimiter)
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
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		if (idx > 1)
			write(fd, "\n", 1);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}
