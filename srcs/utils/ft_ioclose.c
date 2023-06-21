#include "minishell.h"

void	ft_ioclose(t_table_of_commands toc)
{
	int	line;

	line = -1;
	while (++line < toc.size)
	{
		close(toc.inputs[line]);
		close(toc.outputs[line]);
	}
}