#include "minishell.h"

void	ft_tocprint(t_table_of_commands	toc)
{
	int	command_line;
	int	column;

	command_line = 0;
	printf("%d\n", toc.size);
	while (command_line < toc.size)
	{
		column = -1;
		while (++column < 3)
			printf("[%s]", toc.table[command_line][column]);
		printf("\n");
		command_line++;
	}
}