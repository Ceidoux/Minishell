#include "minishell.h"

static char	*ft_prompt(char **envp);
unsigned char	g_exit_status = 0;

int main(int argc, char **argv, char **envp)
{
	(void)	argc, (void) argv;
	char			*line_read;
	char			*prompt;
	t_list			*lst_of_tokens;

	prompt = ft_prompt(envp);
	line_read = readline(prompt);
	lst_of_tokens = ft_parse(line_read, envp);
	ft_lstprint(lst_of_tokens);
	ft_lstclear(&lst_of_tokens, &free);
	return (free(line_read), free(prompt), g_exit_status);
}

static char	*ft_prompt(char **envp)
{
	char	*prompt;

	prompt = ft_strjoin(ft_get_var("USER", envp), (" %>"));
	return (prompt);
}

/*
format du prompt :
	user@hostname cwd %
nb : impossible d'affichier l'hostname sans la fonction uname(), gethostname() ou set()

Attention à check si toutes les variables existent pour ft_prompt
*/