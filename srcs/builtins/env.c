#include "minishell.h"

static int	ft_has_equal_sign(char *s);

int	ft_env(t_tools tools, t_cmd_tab toc, char **envp)
{
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
	{
		ft_pipe_manager(tools, toc);
		while (*envp)
		{
			if (ft_has_equal_sign(*envp))
				ft_putendl_fd(*(envp), 1);
			envp++;
		}
		exit(0);
	}
	return (0);
}

static int	ft_has_equal_sign(char *s)
{
	while (*s)
	{
		if (*s == '=')
			return (1);
		s++;
	}
	return (0);
}

/*
A gérer (pas d'option, pas d'argument):
[ok] env
[*]	si export zzz	-> env n'affiche pas zzz (alors que export le fait)
*/