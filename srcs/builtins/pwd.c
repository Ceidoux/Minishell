#include "minishell.h"

int	invalid_option(char *str)
{
	int	change_fd;

	change_fd = dup(STDOUT_FILENO);
	dup2(STDOUT_FILENO, STDERR_FILENO);
	if (str [0] && str[0] == '-')
	{
		if (str[1] && str[1] != '-')
		{
			pipex_printf("pwd: -%c: invalid option\n", str[1]);
			pipex_printf("pwd: usage: pwd [-LP]\n");
			dup2(STDOUT_FILENO, change_fd);
			close(change_fd);
			return (1);
		}
		else if (str[1] && str[1] == '-' 
			&& str[2])
		{
			pipex_printf("pwd: --: invalid option\n");
			pipex_printf("pwd: usage: pwd [-LP]\n");
			dup2(STDOUT_FILENO, change_fd);
			close(change_fd);
			return (1);
		}
	}
	dup2(STDOUT_FILENO, change_fd);
	close(change_fd);
	return (0);
}
int	ft_pwd(t_tools tools, t_cmd_tab toc)
{
	char *current_dir;

	if (tools.args[1])
	{
		if (invalid_option(tools.args[1]))
		{
			g_exit_status = 2;
			return (0);
		}
	}
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
	{
		ft_pipe_manager(tools, toc);
		current_dir = NULL;
		current_dir = getcwd(current_dir, 4096);
		if (!current_dir)
		{
			perror("pwd");
				exit(1);
		}
		ft_putendl_fd(current_dir, 1);
		free(current_dir);
		exit(0);
	}
	return (0);
}

/*
A gérer (pas d'option)
[ok] pwd
[**] pwd qqc	-> print error: pwd: too many arguments
*/