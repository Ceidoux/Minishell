#include "minishell.h"

int	ft_pwd(void)
{
	char *current_dir;
	
	current_dir = NULL;
	current_dir = getcwd(current_dir, 4096);
	if (!current_dir)
	{
		perror("pwd");
		return (1);
	}
	ft_putendl_fd(current_dir, 1);
	free(current_dir);
	return (0);
}

/*
A gérer (pas d'option)
[ok] pwd
[**] pwd qqc	-> print error: pwd: too many arguments
*/