#include "minishell.h"

void	ft_tocprint(t_table_of_commands	toc)
{
	int	line;

	line = 0;
	printf("Size = %d\n", toc.size);
	if (toc.size)
	{
		printf("[command][input fd][output fd]\n");
		while (line < toc.size)
		{
			printf("[%s]", toc.commands[line]);
			printf("[%d]", toc.inputs[line]);
			printf("[%d]", toc.outputs[line]);
			printf("\n");
			line++;
		}
	}
}