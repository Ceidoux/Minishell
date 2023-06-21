#include "minishell.h"

static char	*ft_prompt(char **envp);
unsigned char	g_exit_status = 0;

int main(int argc, char **argv, char **envp)
{
	(void) argc, (void) argv;
	char				*line_read;
	char				*prompt;
	t_table_of_commands	toc;

	prompt = ft_prompt(envp);
	line_read = readline(prompt);
	toc = ft_parser(line_read, envp);
	return (free(line_read), free(prompt), ft_ioclose(toc), ft_tocfree(&toc), g_exit_status);
}

static char	*ft_prompt(char **envp)
{
	char	*prompt;
	char	*user;

	user = ft_get_var("USER", envp);
	if (!user)
		prompt = ft_strdup("%> ");
	else
		prompt = ft_strjoin(user, (" %> "));
	return (prompt);
}

/*
format du prompt :
	user@hostname cwd %
nb : impossible d'affichier l'hostname sans la fonction uname(), gethostname() ou set()

Attention à check si toutes les variables existent pour ft_prompt
*/