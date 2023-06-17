#include "minishell.h"

static char	*ft_prompt(char **envp);

int main(int argc, char **argv, char **envp)
{
	(void)	argc;
	(void)	argv;
	unsigned char	exit_status;
	char			*line;
	char			*prompt;
	t_list			*tokens;

	exit_status = 0;
	prompt = ft_prompt(envp);
	line = readline(prompt);
	tokens = ft_parse(line);
	return (free(line), free(tokens), exit_status);
}

static char	*ft_prompt(char **envp)
{
	return ("$>");
}

/*
static char	*ft_prompt(char **envp)
{
	char	*prompt;
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
*/

/*
format du prompt :
	user@hostname cwd %
nb : impossible d'affichier l'hostname sans la fonction uname(), gethostname() ou set()

Attention à check si toutes les variables existent pour ft_prompt
*/