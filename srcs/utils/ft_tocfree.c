#include "minishell.h"

void	ft_tocfree(t_table_of_commands *toc)
{
	int	line;
	int	column;

	line = toc->size;
	while (--line >= 0)
	{
		column = -1;
		while (++column < 3)
			free(toc->table[line][column]);
	}
}

