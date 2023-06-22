#include "minishell.h"

int	ft_heredoc(char *delimiter)
{
	int		fd;
	char	*line;
	int		idx;

	fd = open("bash_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0666);
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
	fd = open("bash_heredoc", O_RDONLY);
	unlink("bash_heredoc");
	return (fd);
}
