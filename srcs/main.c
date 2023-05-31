#include "minishell.h"

static void	ft_prompt(char **envp);

int	main(void)
{
	printf("%d\n", ft_)
}

// int main(int argc, char **argv, char **envp)
// {
// 	(void)			argc;
// 	(void)			argv;
// 	char			*s;
// 	unsigned char	exit_status;

// 	exit_status = 0;
// 	while (1)
// 	{
// 		ft_prompt(envp);
// 		s = ft_remove_endl(get_next_line(0));
// 		if (!ft_strncmp(s, "pwd\0", 4))
// 			exit_status = ft_pwd();
// 		else if (!ft_strncmp(s, "env\0", 4))
// 			exit_status = ft_env(envp);
// 		else if (!ft_strncmp(s, "echo ", 5) || !ft_strncmp(s, "echo\0", 5))
// 			exit_status = ft_echo(s, envp);
// 		else if (!ft_strncmp(s, "cd ", 3) || !ft_strncmp(s, "cd\0", 3))
// 			exit_status = ft_cd(s + 2, envp);
// 		else if (!ft_strncmp(s, "exit ", 5) || !ft_strncmp(s, "exit\0", 5))
// 		{
// 			exit_status = ft_exit(s + 4, exit_status);
// 			free(s);
// 			break ;
// 		}
// 		else if ((*s))
// 			printf("zsh: command not found: %s\n", s);
// 		free(s);
// 	}
// 	return (exit_status);
// }

static void	ft_prompt(char **envp)
{
	char	*current_dir;
	int 	i;

	ft_putstr_fd(ft_get_var("USER", envp, 4), 1);
	ft_putchar_fd(' ', 1);
	current_dir = NULL;
	current_dir = getcwd(current_dir, 1);
	if (current_dir)
	{
		i = 0;
		while (current_dir[i])
			i++;
		while (i >= 0 && current_dir[i] != '/')
			i--;
		ft_putstr_fd(current_dir + i + 1, 1);
		free(current_dir);
	}
	ft_putstr_fd(" % ", 1);
}

/*
format du prompt :
	user@hostname cwd %
nb : impossible d'affichier l'hostname sans la fonction uname(), gethostname() ou set()

Attention à check si toutes les variables existent pour ft_prompt
*/