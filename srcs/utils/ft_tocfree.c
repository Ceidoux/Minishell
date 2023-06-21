#include "minishell.h"

void	ft_tocfree(t_table_of_commands *toc)
{
	ft_tocfreetable(toc);
	free(toc);
	toc = NULL;
}

void	ft_tocfreetable(t_table_of_commands *toc)
{
	int	column;

	while (--toc->size >= 0)
	{
		column = -1;
		while (++column < 3)
			free(toc->table[toc->size][column]);
	}
}

