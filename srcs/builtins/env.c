#include "minishell.h"

int	ft_env(char **envp)
{
	while (*envp)
		ft_putendl_fd(*(envp++), 1);
	return (0);
}

/*
A gérer (pas d'option, pas d'argument):
[ok] env
*/