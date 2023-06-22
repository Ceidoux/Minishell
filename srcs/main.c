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
	while (1)
	{
		line_read = readline(prompt);
		add_history(line_read);
		toc = ft_parser(line_read, envp);
		free(line_read);
		ft_tocfree(&toc);
		ft_ioclose(toc);
	}
	return (free(prompt), g_exit_status);
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
! théoriquement, le format du prompt est donné par la variable PS1:
Exemple:
$>echo $PS1
$>%n@%m %1~ %#		->Signifie que le prompt est au format suivant:	user@hostname cwd %
Nb : impossible d'affichier l'hostname sans la fonction uname(), gethostname() ou set()

Attention à check si toutes les variables existent pour ft_prompt

(Et, en principe, $PS2 est utilisé pour les prompt des heredocs)
*/