#include "minishell.h"

void	ft_ioclose(t_table_of_commands toc)
{
	int	line;

	line = -1;
	while (++line < toc.size)
	{
		if (toc.inputs[line] > 0)
			close(toc.inputs[line]);
		if (toc.outputs[line] > 0)
			close(toc.outputs[line]);
	}
}
