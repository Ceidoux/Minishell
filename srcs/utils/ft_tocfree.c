#include "minishell.h"

void	ft_tocfree(t_table_of_commands *toc)
{
	int	line;

	line = toc->size;
	while (--line >= 0)
	{
		free(toc->commands[line]);
		toc->commands[line] = NULL;
	}
	if (toc->size)
	{
		free(toc->inputs);
		toc->inputs = NULL;
		free(toc->outputs);
		toc->outputs = NULL;
	}	
	toc->size = 0;
}

